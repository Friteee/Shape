#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "static_object.h"

namespace game
{

class Tile : public Static_object
{
public:
    Tile();
    virtual void show()override;
    void init_geometry(physics::Geometry init_polygon);
    void init_tile_type();
    void set_x(int x);
    void set_y(int y);
private:


};

}

#endif // TILE_H_INCLUDED
