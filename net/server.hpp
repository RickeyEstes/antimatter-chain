#ifndef __SERVER__HPP__
#define __SERVER__HPP__
#include <list>
#include <memory>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include "client_item.hpp"
#include "config/config.hpp"
class Server{
public:
    Server(boost::asio::io_context& ioc, std::shared_ptr<Config> config_in);
    ~Server();
public:
    void Start();
    std::list<std::shared_ptr<ClientItem>> GetClientList();
private:
    void OnAccept(std::shared_ptr<ClientItem> new_item,
      const boost::system::error_code& error);
    void OnError(std::shared_ptr<ClientItem> item);
private:
    std::shared_ptr<Config> config;
    boost::asio::io_context& ioc;
    boost::asio::io_service::work work;
    boost::asio::ip::tcp::acceptor acceptor;
    std::mutex client_list_mutex;
    std::list<std::shared_ptr<ClientItem>> client_list;
};
#endif