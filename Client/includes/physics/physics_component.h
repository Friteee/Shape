#ifndef PHYSICS_COMPONENT_H_INCLUDED
#define PHYSICS_COMPONENT_H_INCLUDED

#include <memory>

#include <SDL.h>
#include "polygon.h"
#include "../game/moving_object.h"

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
    virtual void notify_static(unsigned int point) = 0;
    //notify about collision with moving object
    virtual void notify_moving(Physics_component* moving) = 0;

    virtual SDL_Point get_interpolated_location(unsigned int time) = 0;

    void init(game::Moving_object * init_object , std::shared_ptr<Polygon> init_polygon)
    {
        object = init_object;
        polygon = init_polygon;
    }

    const Polygon & get_polygon()
    {
        return *polygon;
    }

    inline game::Moving_object * get_object()
    {
        return object;
    }

protected:
    // associated moving object
    game::Moving_object     * object;
    // associated polygon
    std::shared_ptr<Polygon>  polygon;
};

}

#endif // PHYSICS_COMPONENT_H_INCLUDED
