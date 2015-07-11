#ifndef STOPWATCH_H_INCLUDED
#define STOPWATCH_H_INCLUDED

namespace utility
{

/** \brief Stopwatch
 *
 *  Utilizes SDL_GetTicks() function
 *
 */

class Stopwatch
{
public:

    Stopwatch();
    // start the timer
    void start();
    // stop the timer
    void stop();
    // pause the timer
    void pause();
    // set ticks to current
    void reload();
    // getter of ticks
    unsigned int get_ticks();

private:

    // integer to hold current ticks since the start/reload
    unsigned int started_ticks_;
    // in case timer is pausekd
    unsigned int paused_ticks_;
    // boolean to know if timer is paused and started
    bool paused_,started_;
};

}// end of utility namespace

#endif // TIMER_H_INCLUDED
