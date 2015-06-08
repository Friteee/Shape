
#include "tile.h"

namespace game
{

Tile::Tile()
{
    polygon = nullptr;
}

void Tile::show()
{

}

void Tile::init_geometry(physics::Geometry init_polygon)
{
    if(polygon != nullptr)
        delete polygon;
    polygon = new physics::Geometry;
    *polygon = init_polygon;
}

void Tile::init_tile_type()
{

}

void Tile::set_x(int x)
{
    location.x = x;
}

void Tile::set_y(int y)
{
    location.y = y;
}

}
