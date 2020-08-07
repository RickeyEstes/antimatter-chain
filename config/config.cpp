#include "config.hpp"
std::shared_ptr<Config> Config::instance = nullptr;
Config::~Config(){
    
}

std::shared_ptr<Config> Config::GetInstance(){
    if(instance){
        return instance;
    }
    instance = std::shared_ptr<Config>(new  Config());
    return instance;
}

Config::Config(){
    net_config = std::make_shared<NetConfig>();
}
