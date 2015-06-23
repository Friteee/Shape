#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED

#include <boost/asio.h>


namespace network
{

enum Packet_type
{
    CLIENT_COMMAND , CLIENT_UPDATE , PARTIAL_SERVER_UPDATE , FULL_SERVER_UPDATE
};

class Packet
{
public:
private:

};

}

#endif // PACKET_H_INCLUDED
