#ifndef MOVEMENT_COMMAND_H_INCLUDED
#define MOVEMENT_COMMAND_H_INCLUDED

#include "../game/object_command.h"
#include "../game/moving_object.h"

namespace physics
{

class Movement_command : public game::Object_command
{
public:
    Movement_command(game::Moving_object * object, int init_x , int init_y);
    void redo       (game::Moving_object * object) override;
    void execute    (game::Moving_object * object) override;
private:
    int                   x_ , y_;
    int                   x_before_ , y_before_;
};

}

#endif // MOVEMENT_COMMAND_H_INCLUDED
