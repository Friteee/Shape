#ifndef MOVING_OBJECT_H_INCLUDE
#define MOVING_OBJECT_H_INCLUDE


enum Object_type
{
    PLAYER, BULLET
};

namespace physics
{
    class Physics_component;
}

#include "object_command.h"
#include "object_state.h"
#include "../physics/physics_component.h"

namespace game
{

/** \brief Base class for moving objects
 *
 * Objects, which are not part of the scenery, like player or pickups.
 * Every derived class should initialize object_type to its' type
 *
 */

class Moving_object
{
public:

    virtual void           notify(Object_command * command)        = 0;

    virtual void           update()                                = 0;

    virtual Object_state * get_state()                             = 0;

    virtual int            get_x()                                 = 0;

    virtual int            get_y()                                 = 0;

    virtual void           set_position(int set_x, int set_y)      = 0;
    // notify object about collision with another object
    virtual void           notify_collision(Moving_object * other) = 0;

    inline Object_type     get_type()
    {
        return type_;
    }

protected:
    // the physics part of the moving_object
    std::shared_ptr<physics::Physics_component> physics_component_;
    // type of the moving object
    Object_type                                 type_;
    // newest command to the object
    Object_command                            * oldest_;
    Object_command                            * newest_;
    // current object state
    Object_state                              * current_state_;

};

}// end of gamer namespace

#endif // MOVING_OBJECT_H_INCLUDED
