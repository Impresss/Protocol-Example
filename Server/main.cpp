#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

#include "ocp_protocol.h"

void usage()
{
    std::cout << "Usage: ./Server <port> <code> <userId> <command>" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 5) { usage(); return -1; }
    std::cout << "-----------SERVER-----------" << std::endl;
    OCP req;
    OCP res;
    int eCode;
    int sd;
    int nsd;
    sockaddr_in servAddrInfo;
    sockaddr_in cliAddrInfo;
    socklen_t cliAddrLen = sizeof(cliAddrInfo);
    char buffer[10];

    sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0)
    {
        std::cerr << "socket()" << std::endl;
        return -1;
    }

    memset(&servAddrInfo, 0, sizeof(servAddrInfo));
    servAddrInfo.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddrInfo.sin_port = htons(atoi(argv[1]));
    servAddrInfo.sin_family = AF_INET;

    eCode = bind(sd, (sockaddr*)&servAddrInfo, sizeof(servAddrInfo));
    if (eCode < 0)
    {
        std::cerr << "bind()" << std::endl;
        return -1;
    }

    listen(sd, 3);
    std::cout << "Server listening..." << std::endl;

    nsd = accept(sd, (sockaddr*)&cliAddrInfo, &cliAddrLen);
    if (nsd < 0)
    {
        std::cerr << "accept()" << std::endl;
        return -1;
    }

    req.code = atoi(argv[2]);
    req.userId = atoi(argv[3]);
    req.command = *argv[4];

    memset(&buffer, 0, sizeof(buffer));
    serialize(req, buffer, sizeof(buffer));
    eCode = send(nsd, buffer, sizeof(buffer), 0);
    if (eCode < 0)
    {
        std::cerr << "send()" << std::endl;
        return -1;
    }

    memset(&buffer, 0, sizeof(buffer));
    eCode = recv(nsd, buffer, sizeof(buffer), 0);
    if (eCode < 0)
    {
        std::cerr << "recv()" << std::endl;
        return -1;
    }
    deserialize(res, buffer, sizeof(buffer));

    std::cout << "In char array: ";
    for (int i = 0; i < sizeof(buffer); i++)
    {
        if (buffer[i] == '\0')
        {
            break;
        }
        std::cout << buffer[i];
    }
    std::cout << std::endl;

    std::cout << "In protocol type: " << std::endl;
    std::cout << "Response code: " << res.code << std::endl;
    std::cout << "UserId: " << res.userId<< std::endl;
    std::cout << "Command: " << res.command << std::endl;
    std::cout << std::endl;

    close(sd);
    close(nsd);

    return 0;
}
