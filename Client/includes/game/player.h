#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <mutex>
#include "moving_object.h"


namespace game
{

class Player : public Moving_object
{
public:

    void           notify(Object_command * command)override;

    void           update()override;

    Object_state * get_state()override;

    int            get_x()override;

    int            get_y()override;

    void           set_position(int set_x, int set_y)override;

protected:
    int        x_ , y_;
    std::mutex command_mutex_;


};

}

#endif // PLAYER_H_INCLUDED
