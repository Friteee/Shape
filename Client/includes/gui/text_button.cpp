#include "text_button.h"
#include <functional>
#include "../utility/configuration.h"
#include "../utility/functions.h"
#include "../utility/stopwatch.h"
#include <vector>
#include <cstdio>

namespace gui
{

/**
 * Text button constructor
 */

Text_button::Text_button(utility::Configuration * config , std::string init_text , int x , int y)
{
    visible_ = true;

    text_ = init_text;

    size_ = 64;

    std::vector<int> colors = utility::get_numbers_from_string(config->find_string("button_color"));
    color_.r = colors[0];
    color_.g = colors[1];
    color_.b = colors[2];
    color_.a = 255;

    font_file_ = config->find_string("font");
    TTF_Font * font = TTF_OpenFont(font_file_.c_str(),size_);
    if(font == nullptr)
    {
        printf("No font found at %s \n",config->find_string("font").c_str());
    }
    texture_.init(text_,color_,font);

    TTF_CloseFont(font);


    location_.x = x;
    location_.y = y;
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();

    is_clicked_ = false;
}

/**
 * Function to initialize the function for a button to call
 */

void Text_button::init_function(std::function<void()> init_on_click )
{
    on_click_=init_on_click;
}

/**
 * Show function. Nothing to see here
 */

void Text_button::show()
{
    if(!visible_)
    {
        return;
    }
    texture_.blit_on_window(nullptr , &location_);
}

/**
 * Update function
 * Used for handling mouse input and checking whether the button was pressed
 */

void Text_button::update()
{

}

Text_button::~Text_button()
{

}

void Text_button::change_size(unsigned int init_size)
{
    size_ = init_size;
    TTF_Font * font = TTF_OpenFont(font_file_.c_str(),size_);
    texture_.init(text_,color_,font);
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();
}

void Text_button::change_text(std::string init_text)
{
    text_ = init_text;
    TTF_Font * font = TTF_OpenFont(font_file_.c_str(),size_);
    texture_.init(text_,color_,font);
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();
}

void Text_button::handle_click(int x, int y)
{
    if(visible_ && x > location_.x && x < location_.x + location_.w && y > location_.y && y < location_.y + location_.h)
    {
        if(on_click_)
            on_click_();
        else
            printf("Warning : no function specified for a button\n");
        is_clicked_=false;
    }
}

}
