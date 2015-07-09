#ifndef MOVING_OBJECT_H_INCLUDED
#define MOVING_OBJECT_H_INCLUDED

namespace game
{
    class Moving_object;
}
namespace physics
{
    class Physics_component;
}

enum Object_type
{
    PLAYER, BULLET
};

#include "object_command.h"
#include "object_state.h"
#include "../physics/physics_component.h"
#include "../video/render_component.h"
#include "../physics/movement_command.h"

namespace game
{

/** \brief Base class for moving objects
 *
 * Objects, which are not part of the scenery, like player or pickups
 *
 */

class Moving_object
{
public:
    virtual void           notify(Object_command * command) = 0;
    virtual void           update() = 0;
    virtual SDL_Point      get_position() = 0;
    virtual Object_state * get_state() = 0;
private:

    virtual void set_position(int set_x, int set_y) = 0;

    physics::Physics_component * physics_component;
    Object_command             * first;
    Object_type                type;

    friend physics::Movement_command;
};

}// end of gamer namespace

#endif // MOVING_OBJECT_H_INCLUDED
