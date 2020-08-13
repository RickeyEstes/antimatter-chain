#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/asio.hpp>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>
#include "net/server.hpp"
BOOST_AUTO_TEST_SUITE(NetTest)
BOOST_AUTO_TEST_CASE(SampleTest){
    boost::asio::io_context ioc;
    std::shared_ptr<Config> server_config = std::make_shared<Config>();
    server_config->net_config->lession_port=1111;
    std::shared_ptr<Server> server = std::make_shared<Server>(ioc, server_config);
    //std::shared_ptr<ClientItem> peer = std::make_shared<ClientItem>(ioc);
    std::vector<std::shared_ptr<std::thread>> thread_list;
    for(auto i = 0; i < std::thread::hardware_concurrency(); i++){
        thread_list.push_back(std::make_shared<std::thread>(boost::bind(&boost::asio::io_context::run, &ioc)));
    }
    ioc.stop();
    for(auto i = 0; i < std::thread::hardware_concurrency(); i++){
        thread_list[i]->join();
    }
    BOOST_CHECK(1);
}
BOOST_AUTO_TEST_SUITE_END()