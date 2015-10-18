#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include <SDL.h>
#include "../physics/polygon.h"
#include "object_type.h"

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
    Static_object();
    ~Static_object();
    void show();
    void init_geometry(physics::Polygon init_polygon);
    void init_tile_type(Object_type * init_type);
    void set_x(int x);
    void set_y(int y);
    void set_location(SDL_Point location);
    inline Object_type * get_tile_type()
    {
        return type_;
    }
    inline physics::Polygon & get_polygon()
    {
        return polygon_;
    }
protected:
    Object_type    * type_;
    SDL_Point        location_;
    physics::Polygon polygon_;
};

}

#endif // GAME_OBJECT_H_INCLUDED
