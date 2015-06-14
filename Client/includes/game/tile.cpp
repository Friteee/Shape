
#include "tile.h"
#include "../main_logic/game_logic.h"

namespace game
{

Tile::Tile()
{
    main_logic::Game_logic::get_engine().add_static_polygon(&polygon);
}

Tile::~Tile()
{
    main_logic::Game_logic::get_engine().delete_static_polygon(&polygon);
}

void Tile::show()
{
    type->blit(location);
}

void Tile::init_geometry(physics::Geometry init_polygon)
{
    polygon = init_polygon;
}

void Tile::init_tile_type(Tile_type * init_type)
{
    type = init_type;
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
