#include <iostream>
#include "net/net.hpp"
#include "config/config.hpp"
//#include "log/log.hpp"
#include "net/client_item.hpp"

int main(int argc, char** argv){
    auto config = Config::GetInstance();
    AntNet net;
    net.Start();
    getchar();
    return 0;
}