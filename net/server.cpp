#include <functional>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>
#include "server.hpp"
#include "config/config.hpp"
#include "log/log.hpp"
Server::Server():
    ioc(std::thread::hardware_concurrency()),
    work(ioc),
    acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), Config::GetInstance()->net_config->lession_port), false){

}

Server::~Server(){

}

void Server::Start(){
    std::shared_ptr<ClientItem> new_item = std::make_shared<ClientItem>(ioc);
    std::cout<<new_item.get()<<std::endl;
    acceptor.async_accept(
        new_item->GetSocket(),
        std::bind(&Server::OnAccept, this, new_item,
        std::placeholders::_1));
    ioc_thread = std::shared_ptr<std::thread>(new std::thread(boost::bind(&boost::asio::io_context::run, &ioc)));
}

void Server::OnAccept(std::shared_ptr<ClientItem> new_item, const boost::system::error_code& error){
    client_list.push_back(new_item);
    //std::cout<<new_item->GetLocalEndpoint()<<std::endl;
    new_item->Start();
    LogDebug("yes123");
}