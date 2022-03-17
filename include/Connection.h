#ifndef CONNECTION_H
#define CONNECTION_H

#include <vector>
#include <string>

struct Connection
{
    int target;
    std::vector<int> connected;
};

extern std::vector<Connection> connections;

#endif // CONNECTION_H
