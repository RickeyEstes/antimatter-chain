#include "config.hpp"
#include <iostream>
#include <boost/program_options.hpp>
std::shared_ptr<Config> Config::instance = nullptr;

Config::Config(){
    net_config = std::make_shared<NetConfig>();
}

Config::~Config(){
    
}

std::shared_ptr<Config> Config::GetInstance(int argc, char** argv){
    if(instance){
        return instance;
    }
    instance = std::shared_ptr<Config>(new  Config(argc, argv));
    return instance;
}

Config::Config(int argc, char** argv){
    std::cout<<9999<<std::endl;
    boost::program_options::options_description opt("demo option");
    net_config = std::make_shared<NetConfig>();
    opt.add_options()
        ("help", "just help info")
        ("lession_port,P", boost::program_options::value<uint16_t>()->default_value(9987), "Server lession port");
    boost::program_options::variables_map option_map;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opt), option_map);
    if(option_map.count("help")){
        std::cout<<opt<<std::endl;
        exit(0);
    }
    if(option_map.count("lession_port")){
        net_config->lession_port = option_map["lession_port"].as<uint16_t>();
    }
    std::cout<<net_config->lession_port<<std::endl;
    
}
