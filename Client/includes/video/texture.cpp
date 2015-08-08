// *** ADDED BY HEADER FIXUP ***
#include <cassert>
// *** END ***

#include "texture.h"
#include "video_subsystem.h"
#include "camera.h"
#include <assert.h>
#include <cstdio>

namespace video
{

Texture::Texture()
{
    angle_ = 0;

}

/**
 * Initialize texture with file
 */

void Texture::init(std::string filename)
{
    reset();
    create_surface(filename);
    create_texture(filename);
}

/**
 * Initialize texture with filename and rgb color key
 */
void Texture::init(std::string filename, SDL_Color color_key)
{
    reset();
    create_surface(filename);
    Uint32 key = SDL_MapRGB((*surface_)->format,color_key.r,color_key.g,color_key.b);
    SDL_SetColorKey( *surface_ , SDL_TRUE , key );
    create_texture(filename);
}

/**
 * Initialize texture with a surface
 */
void Texture::init(SDL_Surface * init_surface)
{
    reset();
    if(!init_surface)
    {
        printf("Error : null pointer passed to texture");
        assert(0);
    }
    surface_ = std::make_shared<SDL_Surface*>(init_surface);
    create_texture(std::string("(Surface has no filename)"));
}

void Texture::init(std::string filename, SDL_Rect boundaries)
{
    reset();
    create_surface(filename , boundaries);
    create_texture(filename);

}

/**
 * Initialize texture with a surface
 */
void Texture::init(std::string text, SDL_Color text_color, TTF_Font * font)
{
    if(surface_.unique())
    {
        SDL_DestroyTexture(*texture_);
        SDL_FreeSurface(*surface_);
    }
    texture_.reset();
    surface_.reset();
    surface_ = std::make_shared<SDL_Surface*>(TTF_RenderText_Blended( font, text.c_str(), text_color ));
    create_texture(std::string("Surface is text"));
}

Texture::Texture(Texture const & copied)
{
    surface_ = copied.surface_;
    texture_ = copied.texture_;
}

Texture::Texture(Texture && moved)
{
    surface_ = moved.surface_;
    texture_ = moved.texture_;
    moved.surface_.reset();
    moved.texture_.reset();
}

Texture& Texture::operator=(Texture const & copied)
{
    surface_ = copied.surface_;
    texture_ = copied.texture_;
    return *this;
}

Texture& Texture::operator=(Texture && moved)
{
    surface_ = moved.surface_;
    texture_ = moved.texture_;
    moved.surface_.reset();
    moved.texture_.reset();

    return *this;
}

/**
 * Surface, texture, width and height getters
 */
SDL_Texture * Texture::get_texture()
{
    if(!texture_)
    {
        printf("Warning : nullptr texture is being passed\n");
        printf("Did you forget to initialize texture?\n");
    }
    return *texture_;
}

SDL_Surface * Texture::get_surface()
{
    if(!surface_)
    {
        printf("Warning : nullptr surface is being passed\n");
        printf("Did you forget to initialize texture?\n");
    }
    return *surface_;
}

Texture::~Texture()
{
    if(surface_.unique())
    {
        SDL_FreeSurface(*surface_);
    }
    if(texture_.unique())
    {
        SDL_DestroyTexture(*texture_);
    }
    surface_.reset();
    texture_.reset();
}

unsigned int Texture::get_height()
{
    return (*surface_)->h;
}

unsigned int Texture::get_width()
{
    return (*surface_)->w;
}

int Texture::get_angle()
{
    return angle_;
}

void Texture::set_angle(int init_angle)
{
    angle_=init_angle;
}

void Texture::set_alpha(unsigned int alpha)
{
    if(alpha>255)
        printf("Warning! Alpha passed to texture is more than 255");
    SDL_SetTextureAlphaMod(*texture_, alpha);
}

void Texture::create_surface(std::string filename)
{
    SDL_Surface * init_surface = SDL_LoadBMP(filename.c_str());
    surface_ = std::make_shared<SDL_Surface*>(init_surface);
    if(!init_surface)
    {
        printf("Error : Error creating surface from %s \n", filename.c_str());
        printf("Error code : %s\n",SDL_GetError());
        assert(0);
    }
}

void Texture::create_surface(std::string filename , SDL_Rect boundaries)
{
    SDL_Surface * init_surface = SDL_LoadBMP(filename.c_str());
    SDL_Surface * cropped_surface = SDL_CreateRGBSurface(init_surface->flags, boundaries.w, boundaries.h, init_surface->format->BitsPerPixel, init_surface->format->Rmask, init_surface->format->Gmask, init_surface->format->Bmask, init_surface->format->Amask);
    SDL_BlitSurface(init_surface, &boundaries, cropped_surface, 0);
    SDL_FreeSurface(init_surface);
    surface_ = std::make_shared<SDL_Surface*>(cropped_surface);
    if(!cropped_surface)
    {
        printf("Error : Error creating surface from %s \n", filename.c_str());
        printf("Error code : %s\n",SDL_GetError());
        assert(0);
    }
}

void Texture::create_texture(std::string filename)
{
    SDL_Texture * init_texture = Video_subsystem::create_texture(*surface_);
    texture_ = std::make_shared<SDL_Texture*>(init_texture);
    if(init_texture == nullptr)
    {
        printf("Error : Error creating texture from %s \n", filename.c_str());
        printf("Possible causes - No renderer present \n");
        printf("Error code : %s\n",SDL_GetError());
        assert(0);
    }
    else
    {
        SDL_SetTextureBlendMode(*texture_,SDL_BLENDMODE_BLEND);
    }
}

void Texture::reset()
{
    if(surface_.unique() )
    {
        SDL_FreeSurface (*surface_);
    }

    if(texture_.unique() )
    {
        SDL_DestroyTexture (*texture_);
    }
    surface_.reset();
    texture_.reset();
}

void Texture::blit_on_camera(SDL_Rect * source, SDL_Rect * destination)
{
    video::Camera::blit(*texture_ , source , destination);
}

void Texture::blit_on_window(SDL_Rect * source, SDL_Rect * destination)
{
    video::Video_subsystem::blit(*texture_, source, destination , angle_ , nullptr , SDL_FLIP_NONE);
}

}// end of video namespace
