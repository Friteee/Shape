#include <SDL.h>

#include <stdio.h>
#include "camera.h"
#include "video_subsystem.h"

namespace video
{

// memory allocation for an instance of video_subsytem
Camera *Camera::instance_ = nullptr;


/**
 * Blit function for textures
 */
bool Camera::blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* dest)
{
    SDL_Rect* blit_location = nullptr;
    // boolean to store information, about whether to blit the surface
    bool on_screen = true;
    if (dest)
    {
        if(dest->x + dest->w < Camera::instance_->location_.x || dest->x > Camera::instance_->location_.x + Camera::instance_->location_.w)
        {
            on_screen = false;
        }
        else if(dest->y + dest->h < Camera::instance_->location_.y || dest->y > Camera::instance_->location_.y + Camera::instance_->location_.h)
        {
            on_screen = false;
        }
    }
    if(!on_screen)
    {
        // no need to blit the surface
        return true;
    }
    if(dest)
    {
        blit_location=new SDL_Rect;
        blit_location->x=dest->x - Camera::instance_->location_.x;
        blit_location->y=dest->y - Camera::instance_->location_.y;
        blit_location->h=dest->h;
        blit_location->w=dest->w;
    }

    bool check = Video_subsystem::blit(texture,source,blit_location);
    if(!check)
    {
        delete blit_location;
        return false;
    }
    delete blit_location;
    return true;
}



/**
 * Blit function for textures with angle and flipping
 */
bool Camera::blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* dest, const double angle, const SDL_Point * center , const SDL_RendererFlip flip)
{
    SDL_Rect* blit_location = nullptr;
    // boolean to store information, about whether to blit the surface
    bool on_screen = true;
    if (dest)
    {
        if(dest->x + dest->w < Camera::instance_->location_.x || dest->x > Camera::instance_->location_.x + Camera::instance_->location_.w)
        {
            on_screen = false;
        }
        else if(dest->y + dest->h < Camera::instance_->location_.y || dest->y > Camera::instance_->location_.y + Camera::instance_->location_.h)
        {
            on_screen = false;
        }
    }
    if(!on_screen)
    {
        // no need to blit the surface
        return true;
    }
    if(dest)
    {
        blit_location=new SDL_Rect;
        blit_location->x=dest->x - Camera::instance_->location_.x;
        blit_location->y=dest->y - Camera::instance_->location_.y;
        blit_location->h=dest->h;
        blit_location->w=dest->w;
    }

    bool check = Video_subsystem::blit(texture , source , blit_location , angle , center , flip);
    if(!check)
    {
        delete blit_location;
        return false;
    }
    delete blit_location;
    return true;
}

/**
 * camera getter
 */
Camera& Camera::get_instance()
{
    return *Camera::instance_;
}

/**
 * Function to set position for camera
 */
void Camera::set_position(int init_width , int init_height , int init_x , int init_y)
{
    Camera::instance_->location_.x=init_x;
    Camera::instance_->location_.y=init_y;
    Camera::instance_->location_.w=init_width;
    Camera::instance_->location_.h=init_height;
}
/**
 * Function to set position for camera
 */
void Camera::set_position(SDL_Rect init_location)
{
    Camera::instance_->location_=init_location;
}


/**
 * Function to initialize subsystem with integers
 */
bool Camera::initialize(int init_width , int init_height , int init_x , int init_y)
{
    if(Camera::instance_ != nullptr)
    {
        return true;
    }
    Camera::instance_ = new Camera(init_width , init_height , init_x , init_y);
    return Camera::instance_ != nullptr;
}

/**
 * Function to initialize subsystem with rectangle
 */
bool Camera::initialize(SDL_Rect init_location)
{
    if(Camera::instance_ != nullptr)
    {
        return true;
    }
    Camera::instance_ = new Camera(init_location.w , init_location.h , init_location.x , init_location.y);
    return Camera::instance_ != nullptr;
}

/**
 * private constructor
 */
Camera::Camera(int init_width , int init_height , int init_x , int init_y)
{
    location_.w=init_width;
    location_.h=init_height;
    location_.x=init_x;
    location_.y=init_y;
}

/**
 * Camera movement function
 * As you may guess, moves the camera several pixels away
 */
void Camera::move(int x , int y)
{
    Camera::instance_->location_.x+=x;
    Camera::instance_->location_.y+=y;
}

SDL_Rect Camera::get_position()
{
    return instance_->location_;
}

}// end of video namespace
