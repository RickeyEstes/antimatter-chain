#ifndef __SERVER__HPP__
#define __SERVER__HPP__
#include <list>
#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include "client_item.hpp"
class Server{
public:
    Server();
    ~Server();
public:
    void Start();
private:
    void OnAccept(std::shared_ptr<ClientItem> new_item,
      const boost::system::error_code& error);
private:
    boost::asio::io_context ioc;
    boost::asio::io_service::work work;
    boost::asio::ip::tcp::acceptor acceptor;
    std::shared_ptr<std::thread> ioc_thread;
    std::list<std::shared_ptr<ClientItem>> client_list;
};
#endif