
#include "object_type.h"
#include "../video/camera.h"

namespace game
{

Object_type::Object_type()
{
    invincible_ = false;
}
bool Object_type::get_invincibility()
{
    return invincible_;
}
void Object_type::set_invincibility( bool set_invincible )
{
    invincible_ = set_invincible;
}
void Object_type::init_texture     ( std::string filename)
{
    texture_.init(filename);
}
void Object_type::blit             ( SDL_Point location  )
{
    SDL_Rect dest,src;
    src.x = 0;
    src.y = 0;
    src.w = texture_.get_width();
    src.h = texture_.get_height();
    dest.x = location.x;
    dest.y = location.y;
    dest.w = texture_.get_width();
    dest.h = texture_.get_height();
    texture_.blit_on_camera(&src , &dest);
}

void Object_type::set_id(unsigned int init_id)
{
    id_ = init_id;
}

}
