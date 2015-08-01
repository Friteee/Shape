#ifndef PHYSICS_COMPONENT_H_INCLUDE
#define PHYSICS_COMPONENT_H_INCLUDE

#include <memory>
#include <SDL.h>
#include "polygon.h"
#include "../game/moving_object.h"
#include "../game/static_object.h"

namespace game
{
    class Moving_object;
}

namespace physics
{

/** \brief Base class for physics components of moving objects
 *
 *
 */



class Physics_component
{
public:

    virtual void update(unsigned int time) = 0;
    // number of the point, collided with static object
    virtual void notify_static(unsigned int point , game::Static_object * object) = 0;
    //notify about collision with moving object
    virtual void notify_moving(Physics_component* moving) = 0;

    virtual SDL_Point get_interpolated_location(unsigned int time) = 0;

    virtual ~Physics_component(){}

    void init(game::Moving_object * init_object , std::shared_ptr<Polygon> init_polygon)
    {
        object_ = init_object;
        polygon_ = init_polygon;
    }

    const Polygon & get_polygon()
    {
       return *polygon_;
    }

    inline game::Moving_object * get_object()
    {
        return object_;
    }

protected:
    // associated moving object
    game::Moving_object     * object_;
    // associated polygon
    std::shared_ptr<Polygon>  polygon_;

};

}

#endif // PHYSICS_COMPONENT_H_INCLUDED
