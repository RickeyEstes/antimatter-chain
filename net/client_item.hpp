#ifndef __CLIENT__ITEM__HPP__
#define __CLIENT__ITEM__HPP__
#include <memory>
#include <string>
#include <boost/asio.hpp>

class ClientItem:public std::enable_shared_from_this<ClientItem>{
public:
    ClientItem(boost::asio::io_context& ioc);
public:
    void Start();
public:
    boost::asio::ip::tcp::endpoint GetLocalEndpoint();
    boost::asio::ip::tcp::endpoint GetRemoteEndpoint();
    boost::asio::ip::tcp::socket& GetSocket();
private:
    void OnRead(const boost::system::error_code& error, std::size_t bytes_transferred);
private:
    boost::asio::ip::tcp::socket socket;
    std::string buffer_read_tmp;
    std::string buffer_write_tmp;
    std::string buffer_read;
    std::string buffer_write;
};

#endif
