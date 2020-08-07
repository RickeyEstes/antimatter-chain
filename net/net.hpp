#ifndef __NET__HPP__
#define __NET__HPP__
#include "server.hpp"
class AntNet{
public:
    AntNet();
    ~AntNet();
public:
    void Start();
private:
    Server server;
};
#endif