#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <mutex>
#include "moving_object.h"


namespace game
{

class Player : public Moving_object
{
public:

    Player();

    void           notify(Object_command * command)override;

    void           update()override;

    Object_state * get_state()override;

    int            get_x()override;

    int            get_y()override;

    void           set_position(int set_x, int set_y)override;

    void           notify_collision(Moving_object * other)override;

    void           notify_collision(Static_object * other)override;

    void           show();

protected:
    int              x_ , y_;
    physics::Polygon player_polygon_;
    std::mutex       command_mutex_;


};

}

#endif // PLAYER_H_INCLUDED
