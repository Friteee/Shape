#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <boost/asio.hpp>

namespace network
{
/**
 * This ser
 */
class GameServer
{
public:
    // initialize the client - server connection
    bool init(unsigned int init_port, boost::asio::ip::address init_IP);
    void send_packet();

private:
    unsigned int port;
    boost::asio::ip::adress IP;
    boost::asio::io_service service;
    boost::asio::ip::udp::resolver resolver;
    boost::asio::ip::udp::resolver::query query;


};

}

#endif // CLIENT_H_INCLUDED
