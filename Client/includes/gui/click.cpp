

#include "click.h"

namespace gui
{

bool Click::clicked_last_frame_ = false;

SDL_Point Click::last_click_location_ = SDL_Point {0,0};

bool Click::has_clicked()
{
    return Click::clicked_last_frame_;
}

void Click::set_clicked(bool was_clicked)
{
    Click::clicked_last_frame_ = was_clicked;
}

void Click::set_location(int x, int y)
{
    Click::last_click_location_.x = x;
    Click::last_click_location_.y = y;
}

void Click::get_location(int & x, int & y)
{
    x = Click::last_click_location_.x;
    y = Click::last_click_location_.y;
}

}// end of gui namespace
