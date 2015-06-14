#ifndef PHYSICS_COMPONENT_H_INCLUDED
#define PHYSICS_COMPONENT_H_INCLUDED

#include <SDL.h>
#include "geometry.h"
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

    virtual void update() = 0;

    virtual void notify(SDL_Point collision) = 0;

    virtual SDL_Point get_interpolated_location(unsigned int time) = 0;

    void init(game::Moving_object * init_object)
    {
        init_object = object;
    }

    Geometry * get_polygon()
    {
        return polygon;
    }

private:
    // associated moving object
    game::Moving_object * object;
    //location on map
    SDL_Point             location;
    // associated geometry
    Geometry            * polygon;
};

}

#endif // PHYSICS_COMPONENT_H_INCLUDED
