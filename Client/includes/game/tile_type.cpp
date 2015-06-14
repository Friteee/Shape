
#include "tile_type.h"
#include "../video/camera.h"

namespace game
{

Tile_type::Tile_type()
{
    invincible = false;
}
bool Tile_type::get_invincibility()
{
    return invincible;
}
void Tile_type::set_invincibility( bool set_invincible )
{
    invincible = set_invincible;
}
void Tile_type::init_texture     ( std::string filename)
{
    texture.init(filename);
}
void Tile_type::blit             ( SDL_Point location  )
{
    SDL_Rect dest,src;
    src.x = 0;
    src.y = 0;
    src.w = texture.get_width();
    src.h = texture.get_height();
    dest.x = location.x;
    dest.y = location.y;
    dest.w = texture.get_width();
    dest.h = texture.get_height();
    video::Camera::blit(texture.get_texture() , &src , &dest);
}

}
