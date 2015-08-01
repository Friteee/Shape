#ifndef MOVING_OBJECT_H_INCLUDE
#define MOVING_OBJECT_H_INCLUDE

namespace physics
{
    class Physics_component;
}

#include "object_command.h"
#include "static_object.h"
#include "object_state.h"
#include "../physics/physics_component.h"

namespace game
{

enum Moving_object_type
{
    PLAYER, BULLET
};

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
    // set position of moving object (the top right corner of it)
    virtual void           set_position(int set_x, int set_y)      = 0;
    // notify object about collision with another moving object
    virtual void           notify_collision(Moving_object * other) = 0;
    // notify object about collision with another static object
    virtual void           notify_collision(Static_object * other) = 0;
    //show function
    virtual void           show() = 0;

    virtual void           change_state(Object_state & init_state) = 0;

    virtual ~Moving_object(){}

    inline Moving_object_type get_type()
    {
        return type_;
    }

    inline physics::Physics_component * get_physics_component()
    {
        return physics_component_.get();
    }

protected:
    // the physics part of the moving_object
    std::shared_ptr<physics::Physics_component> physics_component_;
    // type of the moving object
    Moving_object_type                          type_;
    // newest command to the object
    Object_command                            * oldest_;
    Object_command                            * newest_;
    // current object state
    Object_state                              * current_state_;

};

}// end of gamer namespace

#endif // MOVING_OBJECT_H_INCLUDED
