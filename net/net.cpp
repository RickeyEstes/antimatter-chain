#include "net.hpp"
#include "log/log.hpp"
AntNet::AntNet(std::shared_ptr<Config> config_in):config(config_in),server(config){}
AntNet::~AntNet(){}
void AntNet::Start(){
    server.Start();
}

