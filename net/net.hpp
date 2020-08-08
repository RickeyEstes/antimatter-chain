#ifndef __NET__HPP__
#define __NET__HPP__
#include "server.hpp"
#include "config/config.hpp"
class AntNet{
public:
    AntNet(std::shared_ptr<Config> config_in);
    ~AntNet();
public:
    void Start();
private:
    std::shared_ptr<Config> config;
    Server server;
};
#endif