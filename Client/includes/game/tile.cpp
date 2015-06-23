
#include "tile.h"
#include "../main_logic/game_logic.h"

namespace game
{

Tile::Tile()
{
    type = nullptr;
}

Tile::~Tile()
{
    if(!type->get_invincibility())
        main_logic::Game_logic::get_engine().delete_static_object(&polygon);
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
    if(type != nullptr && type->get_invincibility())
    {
        main_logic::Game_logic::get_engine().delete_static_object(&polygon);
    }
    type = init_type;
    if(!type->get_invincibility())
    {
        main_logic::Game_logic::get_engine().add_static_object(&polygon);
    }
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
