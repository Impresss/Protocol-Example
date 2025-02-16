#include <cstddef>
#include <iostream>

typedef struct ocp_protocol
{
    int code;
    int userId;
    char command;
} OCP;

void serialize(OCP &ocp, char *buffer, size_t bufferSize)
{
    // OCP[data] -> buffer
    if (bufferSize < 3) { std::cerr << "BufferSize must be at min 3" << std::endl; }
    buffer[0] = static_cast<char>(ocp.code);
    buffer[1] = static_cast<char>(ocp.userId);
    buffer[2] = ocp.command;
}


void deserialize(OCP &ocp, char *buffer, size_t bufferSize)
{
    // buffer -> OCP[data]
    if (bufferSize < 3) { std::cerr << "BufferSize must be at min 3" << std::endl; }
    ocp.code = static_cast<int>(buffer[0]);
    ocp.userId = static_cast<int>(buffer[1]);
    ocp.command = buffer[2];
}
