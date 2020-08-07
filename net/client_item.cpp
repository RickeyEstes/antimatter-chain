#include "client_item.hpp"
#include "log/log.hpp"
#include "tool/string_tools.hpp"
ClientItem::ClientItem(boost::asio::io_context& ioc):socket(ioc)
{

}

void ClientItem::Start(){
    buffer_read_tmp.resize(1024*1024*10);
    buffer_write_tmp.resize(1024*1024*10);
    std::cout<<shared_from_this().get()<<std::endl;
    socket.async_read_some(boost::asio::buffer(buffer_read_tmp), std::bind(&ClientItem::OnRead, shared_from_this(),  std::placeholders::_1, std::placeholders::_2));
    //boost::asio::buffer dd;
}

boost::asio::ip::tcp::endpoint ClientItem::GetLocalEndpoint(){
    return socket.local_endpoint();
}

boost::asio::ip::tcp::endpoint ClientItem::GetRemoteEndpoint(){
    return socket.remote_endpoint();
}

boost::asio::ip::tcp::socket& ClientItem::GetSocket(){
    return socket;
}

void ClientItem::OnRead(const boost::system::error_code& error, std::size_t bytes_transferred){
    if(error){
        LogWarning("OnReadError:"+ error.message());
        return;
    }else{
        LogDebug("Readed "<<bytes_transferred<<" bytes")
        buffer_read.append(buffer_read_tmp, 0, bytes_transferred);
        socket.async_read_some(boost::asio::buffer(buffer_read_tmp), std::bind(&ClientItem::OnRead, shared_from_this(),  std::placeholders::_1, std::placeholders::_2));
        LogDebug("Readed "<<String2Hex(buffer_read)<<" bytes");
    }
}