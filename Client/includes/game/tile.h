#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "static_object.h"
#include "tile_type.h"

namespace game
{

/** \brief Tile object
 *
 *  Can be invincible
 *  Made to be held by Map object
 */


class Tile : public Static_object
{
public:
    Tile();
    ~Tile();
    virtual void show()override;
    void init_geometry(physics::Geometry init_polygon);
    void init_tile_type(Tile_type * init_type);
    void set_x(int x);
    void set_y(int y);
private:
    Tile_type * type;
};

}

#endif // TILE_H_INCLUDED
