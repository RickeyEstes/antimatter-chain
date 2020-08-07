#ifndef __CONFIG__HPP__
#define __CONFIG__HPP__

#include <string>
#include <memory>

struct NetConfig{
    uint16_t lession_port = 9987;
};
class Config{
public:
    ~Config();
    static std::shared_ptr<Config> GetInstance();
private:
    Config();
public:
    std::shared_ptr<NetConfig> net_config;
    static std::shared_ptr<Config> instance;
};

#endif
