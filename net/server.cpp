#include <functional>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>
#include "server.hpp"
#include "log/log.hpp"
Server::Server(boost::asio::io_context& ioc, std::shared_ptr<Config> config_in):
    config(config_in),
    ioc(ioc),
    work(ioc),
    acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), config->net_config->lession_port), false){
    LogDebug("Server create"<<this);
}

Server::~Server(){
    LogDebug("Server desdroy"<<this);
}

void Server::Start(){
    std::shared_ptr<ClientItem> new_item = std::make_shared<ClientItem>(ioc, std::bind(&Server::OnError,this, std::placeholders::_1));
    acceptor.async_accept(
        new_item->GetSocket(),
        std::bind(&Server::OnAccept, this, new_item,
        std::placeholders::_1));
}

void Server::OnAccept(std::shared_ptr<ClientItem> new_item, const boost::system::error_code& error){
    {
        std::lock_guard<std::mutex> lk(client_list_mutex);
        client_list.push_back(new_item);
        LogInfo("Receive a new connection, count "<<client_list.size())
    }
    new_item->Start();
    std::shared_ptr<ClientItem> item = std::make_shared<ClientItem>(ioc, std::bind(&Server::OnError,this, std::placeholders::_1));
    acceptor.async_accept(
        item->GetSocket(),
        std::bind(&Server::OnAccept, this, item,
        std::placeholders::_1));
}

void Server::OnError(std::shared_ptr<ClientItem> item){
    {
        std::lock_guard<std::mutex> lk(client_list_mutex);
        for(auto iter = client_list.begin(); iter != client_list.end(); iter++){
            if(item == *iter){
                client_list.erase(iter);
                LogInfo("Remove a connection, count "<<client_list.size())
                break;
            }
        }
    }
}