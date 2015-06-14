#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include <SDL.h>
#include "../physics/geometry.h"

namespace game
{


class Static_object
{
public:
    virtual void show(){};
protected:
    SDL_Point           location;
    physics::Geometry   polygon;
};

}

#endif // GAME_OBJECT_H_INCLUDED
