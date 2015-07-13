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
    virtual void show() = 0;
    virtual ~Static_object(){}
protected:
    SDL_Point        location_;
    physics::Polygon polygon_;
};

}

#endif // GAME_OBJECT_H_INCLUDED
