#include "text_button.h"
#include <functional>
#include "../video/window.h"
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
    visible = true;

    text = init_text;

    size = 64;

    std::vector<int> colors = utility::get_numbers_from_string(config->find_string("button_color"));
    color.r = colors[0];
    color.g = colors[1];
    color.b = colors[2];
    color.a = 255;

    font_file = config->find_string("font");
    TTF_Font * font = TTF_OpenFont(font_file.c_str(),size);
    if(font == nullptr)
    {
        printf("No font found at %s \n",config->find_string("font").c_str());
    }
    texture.init(text,color,font);

    TTF_CloseFont(font);


    location.x = x;
    location.y = y;
    location.w = texture.get_width();
    location.h = texture.get_height();

    is_clicked = false;
}

/**
 * Function to initialize the function for a button to call
 */

void Text_button::init_function(std::function<void()> init_on_click )
{
    on_click=init_on_click;
}

/**
 * Show function. Nothing to see here
 */

void Text_button::show()
{
    if(!visible)
    {
        return;
    }
    video::Video_subsystem::blit(texture.get_texture(),nullptr,&location);
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
    size = init_size;
    TTF_Font * font = TTF_OpenFont(font_file.c_str(),size);
    texture.init(text,color,font);
    location.w = texture.get_width();
    location.h = texture.get_height();
}

void Text_button::change_text(std::string init_text)
{
    text = init_text;
    TTF_Font * font = TTF_OpenFont(font_file.c_str(),size);
    texture.init(text,color,font);
    location.w = texture.get_width();
    location.h = texture.get_height();
}

void Text_button::handle_click(int x, int y)
{
    if(visible && x > location.x && x < location.x + location.w && y > location.y && y < location.y + location.h)
    {
        if(on_click)
            on_click();
        else
            printf("Warning : no function specified for a button\n");
        is_clicked=false;
    }
}

}
