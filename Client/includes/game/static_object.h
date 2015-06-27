#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include <SDL.h>
#include "../physics/polygon.h"

namespace game
{

/** \brief Static_object base class
 *
 *  Consists of a location and geometrical polygon
 *  Has a base function show
 */


class Static_object
{
public:
    virtual void show(){};
protected:
    SDL_Point        location;
    physics::Polygon polygon;
};

}

#endif // GAME_OBJECT_H_INCLUDED
