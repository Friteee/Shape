
#include "tile.h"
#include "../main_logic/game_logic.h"

namespace game
{

Tile::Tile()
{
    type_ = nullptr;
}

Tile::~Tile()
{
    if(!type_->get_invincibility())
        main_logic::Game_logic::get_engine().delete_static_object(&polygon_);
}

void Tile::show()
{
    type_->blit(location_);
}

void Tile::init_geometry(physics::Polygon init_polygon)
{
    polygon_ = init_polygon;
}

void Tile::init_tile_type(Tile_type * init_type)
{
    if(type_ != nullptr && type_->get_invincibility())
    {
        main_logic::Game_logic::get_engine().delete_static_object(&polygon_);
    }
    type_ = init_type;
    if(!type_->get_invincibility())
    {
        main_logic::Game_logic::get_engine().add_static_object(&polygon_);
    }
}

void Tile::set_x(int x)
{
    location_.x = x;
}

void Tile::set_y(int y)
{
    location_.y = y;
}

}
