#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

#include "ocp_protocol.h"

int main()
{
    std::cout << "-----------CLIENT-----------" << std::endl;
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
        exit(EXIT_FAILURE);
    }

    inet_pton(AF_INET, "127.0.0.1", &servAddrInfo.sin_addr.s_addr);
    servAddrInfo.sin_port = htons(65000);
    servAddrInfo.sin_family = AF_INET;

    eCode = connect(sd, (sockaddr*)&servAddrInfo, sizeof(servAddrInfo));
    if (eCode < 0)
    {
        std::cerr << "connect()" << std::endl;
        return -1;
        exit(EXIT_FAILURE);
    }

    memset(&buffer, 0, sizeof(buffer));
    eCode = recv(sd, buffer, sizeof(buffer), 0);
    if (eCode < 0)
    {
        std::cerr << "recv()" << std::endl;
        return -1;
        exit(EXIT_FAILURE);
    }
    deserialize(res, buffer, sizeof(buffer));
    std::cout << "In char array: ";
    for (int i = 0; i < sizeof(buffer); i++)
    {
        if (buffer[i] == '\0') break;
        std::cout << buffer[i];
    }
    std::cout << std::endl;

    std::cout << "In protocol type: " << std::endl;
    std::cout << "Response code: " << res.code << std::endl;
    std::cout << "UserId: " << res.userId << std::endl;
    std::cout << "Command: " << res.command << std::endl;

    req.code = 2;
    req.userId = 1;
    req.command = 'b';
    memset(&buffer, 0, sizeof(buffer));
    serialize(req, buffer, sizeof(buffer));
    eCode = send(sd, buffer, sizeof(buffer), 0);
    if (eCode < 0)
    {
        std::cerr << "send()" << std::endl;
        return -1;
        exit(EXIT_FAILURE);
    }

    close(sd);
}
