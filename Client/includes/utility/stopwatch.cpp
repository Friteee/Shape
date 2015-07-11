#include "stopwatch.h"
#include <SDL.h>

namespace utility
{

/**
 *  Stopwatch constructor
 */
Stopwatch::Stopwatch()
{
    started_ticks_=SDL_GetTicks();
    paused_ticks_=0;
    paused_=false;
    started_=false;
}

/**
 * Function to get ticks from the last time stopwatch was used
 * Ticks are returned as milliseconds, so be cautious when using stopwatch for seconds
 */
unsigned int Stopwatch::get_ticks()
{
    if(!started_)
    {
        return 0;
    }
    else if(paused_)
    {
        return paused_ticks_-started_ticks_;
    }
    else
    {
        return SDL_GetTicks()-started_ticks_;
    }
}

/**
 * Function to start the stopwatch
 */
void Stopwatch::start()
{
    if(paused_==false)
    {
        started_ticks_=SDL_GetTicks();
        started_=true;
    }
    else
    {
        paused_=false;
        started_ticks_=SDL_GetTicks()-paused_ticks_+started_ticks_;
    }
}

/**
 * Function to stop the stopwatch
 */
void Stopwatch::stop()
{
    started_=false;
}

/**
 * Function to pause the stopwatch
 * The stopwatch doesn't count ticks when paused
 */
void Stopwatch::pause()
{
    paused_=true;
}

/**
 * Function to reload the stopwatch to 0 milliseconds
 */
void Stopwatch::reload()
{
    started_ticks_=SDL_GetTicks();
}

}// end of utility namespace

