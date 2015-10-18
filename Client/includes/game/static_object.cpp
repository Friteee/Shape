#include "static_object.h"
#include "../main_logic/game_logic.h"

namespace game
{

Static_object::Static_object()
{
    type_ = nullptr;
    location_.x = 0;
    location_.y = 0;
}

Static_object::~Static_object()
{
    main_logic::Game_logic::get_engine().delete_static_object(this);
}

void Static_object::show()
{
    type_->blit(location_);
}

void Static_object::init_geometry(physics::Polygon init_polygon)
{
    polygon_ = init_polygon;
}

void Static_object::init_tile_type(Object_type * init_type)
{
    if(type_ != nullptr )
    {
        main_logic::Game_logic::get_engine().delete_static_object(this);
    }
    type_ = init_type;
    main_logic::Game_logic::get_engine().add_static_object(this);
}

void Static_object::set_x(int x)
{
    location_.x = x;
}

void Static_object::set_y(int y)
{
    location_.y = y;
}

void Static_object::set_location(SDL_Point location)
{
    location_ = location;
}

}
