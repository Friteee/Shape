#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <boost/asio.hpp>

namespace network
{
/**
 * \brief Server
 *
 *  Server, into which player connects to play the game
 *
 */
class GameServer
{
public:
    // initialize the client - server connection
    bool        init(unsigned int init_port, boost::asio::ip::address init_IP);
    std::string get_maps_name();
    game::Map   get_map();
    void        process_packets();

private:
    unsigned int                          port_;
    boost::asio::ip::adress               IP_;
    boost::asio::io_service               service_;
    boost::asio::ip::udp::resolver        resolver_;
    boost::asio::ip::udp::resolver::query query_;


};

}

#endif // CLIENT_H_INCLUDED
