#ifndef WINDOW_CPP
#define WINDOW_CPP

#include <SDL.h>
#include <stdio.h>
#include "video_subsystem.h"

namespace video
{


// memory allocation for an instance of video_subsytem
Video_subsystem *Video_subsystem::instance_ = nullptr;

/**
 * Function to get video_subsystem
 * returns instance or null if not created
 */
Video_subsystem& Video_subsystem::get_instance()
{
    return *Video_subsystem::instance_;
}

/**
 * function to initialize subsystem
 * returns true on success or if the system was already initialized, false on failure
 */
bool Video_subsystem::initialize_subsystem(int width, int height , bool fullscreen)
{

    if(Video_subsystem::instance_!=nullptr)
    {
        return true;
    }
    Video_subsystem::instance_ = new Video_subsystem (width , height , fullscreen);
    return Video_subsystem::instance_->is_created_ ;
}

/**
 * function to access the sdl_window
 */
SDL_Window* Video_subsystem::get_window()
{
    return main_window_;
}

/**
 * function to access the renderer
 */
SDL_Renderer* Video_subsystem::get_renderer()
{
    return main_renderer_;
}

/**
 * subsystems constructor
 */
Video_subsystem::Video_subsystem(int width , int height , bool fullscreen)
{
    int alright;
    if(fullscreen)
        alright = SDL_CreateWindowAndRenderer(width , height , SDL_WINDOW_FULLSCREEN_DESKTOP , &main_window_ , &main_renderer_);
    else
        alright = SDL_CreateWindowAndRenderer(width , height , 0 , &main_window_ , &main_renderer_);
    if(alright == -1)
    {
        printf("Couldn't initialize video subsystem. \n");
        printf("Error = %s\n",SDL_GetError());
        is_created_=false;
    }
    else
    {
        is_created_=true;
    }
}

Video_subsystem::~Video_subsystem()
{
    SDL_DestroyRenderer(main_renderer_);
    SDL_DestroyWindow(main_window_);
}

/**
 * Function to blit texture straight into screen
 * Use it ONLY for GUI and background
 * returns false on error
 */
bool Video_subsystem::blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* destination)
{
    int error_check = SDL_RenderCopy(Video_subsystem::instance_->main_renderer_ , texture, source, destination);
    if(error_check<0)
    {
        printf("Error blitting on screen.\nError = %s \n" , SDL_GetError());
    }
    return error_check >= 0 ? true : false;
}


/**
 * Reload the screen
 * Sets the screen to black/white
 */
bool Video_subsystem::reload()
{
    int error_check = SDL_RenderClear(Video_subsystem::instance_->main_renderer_);
    if(error_check<0)
    {
        printf("Error clearing the renderer.\nError = %s \n" , SDL_GetError());
    }
    return error_check >= 0 ? true : false;
}

/**
 * Update the screen
 * (Updates the window on screen for user)
 */
void Video_subsystem::update_screen()
{
    SDL_RenderPresent(Video_subsystem::instance_->main_renderer_);
    return ;
}

/**
 * Minimize the window
 * It seems that fps is extremely high when window is minimized
 */

void Video_subsystem::minimize()
{
    SDL_MinimizeWindow(Video_subsystem::instance_->main_window_);
    return;
}

/**
 * Program name setter
 */
void Video_subsystem::set_programs_name(const char * name)
{
    SDL_SetWindowTitle(Video_subsystem::instance_->main_window_,name);
}

/**
 * Wrapper for a texture
 */
SDL_Texture* Video_subsystem::create_texture(SDL_Surface * surface)
{
    SDL_Texture * returned = SDL_CreateTextureFromSurface(Video_subsystem::instance_->main_renderer_,surface);
    return returned;
}


/**
 * Blit function with angle and flipping
 */
bool Video_subsystem::blit(SDL_Texture* texture , SDL_Rect* source , SDL_Rect* destination, const double angle, const SDL_Point * center , const SDL_RendererFlip flip)
{
    int error_check = SDL_RenderCopyEx(Video_subsystem::instance_->main_renderer_, texture, source, destination, angle, center, flip);
    if(error_check<0)
    {
        printf("Error blitting on screen.\nError = %s \n" , SDL_GetError());
    }
    return error_check >= 0 ? true : false;
}


/**
 * Draw line function
 */

void Video_subsystem::draw_line(int x_1 , int y_1 , int x_2 , int y_2,
                                uint8_t r , uint8_t g, uint8_t b )
{
    SDL_SetRenderDrawColor(instance_->main_renderer_ , r , g , b , 255);

    SDL_RenderDrawLine(instance_->main_renderer_, x_1 , y_1 , x_2, y_2);

    SDL_SetRenderDrawColor(instance_->main_renderer_ , 0 , 0 , 0 , 255);
    return;
}

/**
 * Height of the screen getter function
 */
int Video_subsystem::get_height()
{
    int height,width;
    SDL_GetWindowSize(instance_->main_window_ , &width, &height);
    return height;
}

/**
 * Width of the screen getter function
 */
int Video_subsystem::get_width()
{
    int height,width;
    SDL_GetWindowSize(instance_->main_window_ , &width, &height);
    return width;
}


/**
 * \brief Fill rectangle set in SDL_Rect with color r,g,b
 * \param SDL_Rect filling - rect where to blit
 */
void Video_subsystem::fill_rect(SDL_Rect filling, uint8_t r , uint8_t g, uint8_t b)
{
    SDL_SetRenderDrawColor(instance_->main_renderer_ , r , g , b , 255);

    SDL_RenderFillRect(instance_->main_renderer_, &filling);

    SDL_SetRenderDrawColor(instance_->main_renderer_ , 0 , 0 , 0 , 255);
    return;
}

/**
 * \brief Clean after the subsystem
 *
 */
void Video_subsystem::free_subsystem()
{
    if(Video_subsystem::instance_ != nullptr)
    {
        delete Video_subsystem::instance_;
    }
    Video_subsystem::instance_ = nullptr;
}

}// end of namespace

#endif // WINDOW
