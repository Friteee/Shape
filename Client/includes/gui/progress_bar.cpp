// *** ADDED BY HEADER FIXUP ***
#include <cassert>
// *** END ***

#include "progress_bar.h"
#include "../video/video_subsystem.h"
#include<cstdio>
#include<assert.h>

namespace gui
{

void Progress_bar::handle_click(int x, int y)
{
    //do nothing
}

void Progress_bar::show()
{
    texture_.blit_on_window(nullptr , &location_);
    unsigned int red = current_ticks_.get_ticks() * 255 / overall_ticks_;
    unsigned int green = 255 - red;
    video::Video_subsystem::fill_rect(bar_location_,red,green,0);
}

void Progress_bar::update()
{
    if(current_ticks_.get_ticks() >= overall_ticks_)
    {
        if(timer_function_)
        {
            timer_function_();
        }
        else
        {
            printf("No function is given for progress bar\n");
            assert(0);
        }
        current_ticks_.reload();
    }
    bar_location_.w = current_ticks_.get_ticks() * (location_.w-4) / overall_ticks_;
}

void Progress_bar::set_function(std::function<void()> init_function)
{
    timer_function_ = init_function;
}

void Progress_bar::start()
{
    current_ticks_.start();
}

void Progress_bar::reset()
{
    current_ticks_.reload();
}

Progress_bar::Progress_bar(unsigned int init_overall , SDL_Rect init_location)
{
    overall_ticks_ = init_overall;
    location_ = init_location;
    // initializing surface for texture
    SDL_Surface * init_texture = SDL_CreateRGBSurface(0, location_.w, location_.h, 32, 0, 0, 0, 0);
    // Filling the surface with white color.
    SDL_FillRect(init_texture, NULL, SDL_MapRGB(init_texture->format, 255, 255 , 255));
    bar_location_.x = 2 ;
    bar_location_.y = 2 ;
    bar_location_.w = location_.w - 4;
    bar_location_.h = location_.h - 4;
    // Filling the surface with black
    SDL_FillRect(init_texture, &bar_location_, SDL_MapRGB(init_texture->format, 0, 0, 0));
    // Setting black as color key
    Uint32 key = SDL_MapRGB(init_texture->format,0,0,0);
    SDL_SetColorKey( init_texture , SDL_TRUE , key );
    texture_.init( init_texture );

    bar_location_.x = 2 + location_.x;
    bar_location_.y = 2 + location_.y;

}

Progress_bar::~Progress_bar()
{

}

}//end of gui namespace
