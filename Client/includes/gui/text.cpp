

#include "text.h"
#include "../utility/functions.h"
#include <cstdio>

namespace gui
{

Text::Text(utility::Configuration * config, std::string init_text, int x , int y, int init_text_size, SDL_Color init_color_key)
{
    visible_ = true;
    text_ = init_text;
    text_size_ = init_text_size;

    color_key_=init_color_key;
    color_key_.a=255;

    font_ = std::make_shared<TTF_Font*>(TTF_OpenFont(config->find_string("font").c_str(),text_size_));

    if(!text_.empty())
    {
        texture_.init(text_,color_key_,*font_);

        location_.w = texture_.get_width();
        location_.h = texture_.get_height();
    }
    else
    {
        location_.w = 0;
        location_.h = 0;
    }
    location_.x = x;
    location_.y = y;
}

void Text::show()
{
    if(!visible_||text_.length()==0)
    {
        return;
    }
    texture_.blit_on_window(nullptr , &location_);
}

void Text::update()
{

}

Text::~Text()
{
    if(font_.unique())
        TTF_CloseFont(*font_);
}

void Text::change_text(std::string init_text)
{
    if(text_==init_text)
        return;
    text_ = init_text;
    if(text_.length()!=0)
    {
        texture_.init(init_text,color_key_,*font_);
        location_.w = texture_.get_width();
        location_.h = texture_.get_height();
    }
}

void Text::handle_click(int x, int y)
{

}

unsigned int Text::get_length()
{
    return text_.length();
}

}// end of namespace gui
