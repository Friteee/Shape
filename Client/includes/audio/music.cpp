#include "music.h"
#include <cstdio>

namespace audio
{


void Music::init(std::string init_sound)
{

    Mix_Music * buffer = Mix_LoadMUS( init_sound.c_str());
    if( buffer == NULL )
    {
        printf( "Failed to load a sound effect from %s! SDL_mixer Error: %s\n", init_sound.c_str() , Mix_GetError() );
    }
    sound_ = std::make_shared<Mix_Music*>( buffer );
}

void Music::play()
{
    Mix_PlayMusic( *sound_.get(), -1 );
}

void Music::stop()
{
    Mix_HaltMusic();
}

void Music::pause()
{
    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

Music::~Music()
{
    Mix_FreeMusic( *sound_.get() );
}

void Music::change_volume(int amount)
{
    if(volume_ + amount> 128 && amount > 0)
        volume_ = 128;
    else if (volume_ + amount > 128 && amount < 0)
        volume_ = 0;
    else
        volume_ += amount;
    Mix_VolumeMusic(volume_);
}

void Music::set_volume(unsigned int init_volume)
{
    volume_ = init_volume;
    Mix_VolumeMusic(volume_);
}

unsigned int Music::volume_ = 128;

}
