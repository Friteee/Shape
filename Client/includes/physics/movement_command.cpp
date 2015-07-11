#include "movement_command.h"

namespace physics
{

Movement_command::Movement_command(game::Moving_object * object, int init_x , int init_y)
{
    x = init_x;
    y = init_y;
    x_before = object->get_x();
    y_before = object->get_y();
    timestamp = SDL_GetTicks();
    next = nullptr;
    previous = nullptr;

}

void Movement_command::redo(game::Moving_object * object)
{
    object->set_position(x_before,y_before);
}

void Movement_command::execute(game::Moving_object * object)
{
    object->set_position(x,y);
}

}
