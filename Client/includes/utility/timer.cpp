
#include "timer.h"
#include <cstdio>

namespace utility
{

void Timer::set_time(unsigned int init_time)
{
    time_ = init_time;
}

// set function
void Timer::set_function(std::function<void()> init_function)
{
    script_ = init_function;
}
// update the timer to see if
void Timer::update()
{
    if(started_ && stopwatch_.get_ticks() > time_)
    {
        if(script_)
            script_();
        else
            printf("Warning : no function specified for timer\n");
        started_ = false;
        stopwatch_.reload();
        stopwatch_.stop();
    }
}

void Timer::start()
{
    started_ = true;
    stopwatch_.start();
}



}//end of utility namespace
