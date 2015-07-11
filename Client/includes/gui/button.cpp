
#include "button.h"
#include <cstdio>

namespace gui {

Button::Button(int x , int y)
{
    visible_ = true;

    location_.x = x;
    location_.y = y;

}

void Button::init_image(std::string image)
{
    texture_.init(image , SDL_Color{255,0,255,255});
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();
}

void Button::init_image(video::Texture init_texture)
{
    texture_ = init_texture;
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();
}

video::Texture & Button::get_texture()
{
    return texture_;
}

void Button::show()
{
    if(!visible_)
    {
        return;
    }
    texture_.blit_on_window(nullptr , &location_);
}

void Button::update()
{

}

void Button::init_function(std::function<void()> init_on_click)
{
    on_click_ = init_on_click;
}

void Button::handle_click(int x, int y)
{
    if(visible_&& x > location_.x && x < location_.x + location_.w && y > location_.y && y < location_.y + location_.h)
    {
        if(on_click_)
        {
            on_click_();
        }
        else
            printf("Warning : no function specified for a button\n");
    }
}

}
