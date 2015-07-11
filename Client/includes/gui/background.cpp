#include <stdio.h>
#include <SDL.h>
#include <string>
#include <memory>
#include "background.h"

namespace gui
{


/**
 * Default background constructor
 */
Background::Background()
{
    location_.x=0;
    location_.y=0;
    location_.w=0;
    location_.h=0;
}

/**
 * Constructor for background
 * use c style location string
 */
Background::Background(const char* image_location)
{
    texture_.init(image_location);
    location_.x=0;
    location_.y=0;
    location_.w=texture_.get_width();
    location_.h=texture_.get_height();
}

/**
 * Constructor for background
 * overloaded to use shared_ptr
 */
Background::Background(shared_ptr<SDL_Surface*>copied_surface)
{
    texture_.init(*copied_surface);
    location_.x = 0;
    location_.y = 0;
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();
}

/**
 * Copy constructor
 */
Background::Background(const Background &copied_object)
{
    texture_ = copied_object.texture_;
    location_ = copied_object.location_;
}

/**
 * Copy assignment operator
 */
Background& Background::operator=(const Background &copied_object)
{
    if(this!=&copied_object)
    {
        this->texture_ = copied_object.texture_;
        this->location_ = copied_object.location_;
    }
    return *this;
}

/**
 * Move constructor
 */
Background::Background(Background && moved_object)
{
    texture_ = moved_object.texture_;
    location_ = moved_object.location_;
}

/**
 * Move assignment operator
 */
Background & Background::operator=(Background && moved_object)
{
    texture_ = moved_object.texture_;
    location_ = moved_object.location_;
    return *this;
}

/**
 * Destructor
 * Frees the memory for shared pointers
 */
Background::~Background()
{

}

/**
 * Show method
 * Use it to blit background to screen
 */
void Background::show()
{
    texture_.blit_on_window(&location_ , static_cast<SDL_Rect *> (nullptr));
}

/**
 * Method to change image
 * Uses image location string (as for constructor)
 */
void Background::change_image(const char * image_location)
{
    texture_.init(image_location);
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();
}

/**
 * Method to change image
 * Uses shared pointer (as in overloaded constructor)
 */
void Background::change_image(shared_ptr<SDL_Surface*>copied_surface)
{
    texture_.init(*copied_surface);
    location_.w = texture_.get_width();
    location_.h = texture_.get_height();
}


}// end of objects namespace
