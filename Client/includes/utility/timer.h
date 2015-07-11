#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <functional>
#include "stopwatch.h"

namespace utility
{

/** \brief Timer
 *
 *  Executes function on finish
 */

class Timer
{
public:
    // set time in milliseconds (ticks)
    void set_time(unsigned int init_time);
    // set function
    void set_function(std::function<void()> init_function);
    // update the timer to see if
    void update();
    void start();

private:
    // for handling ticks
    Stopwatch stopwatch_;
    // time until next function
    unsigned int time_ = 0;
    // bool if started
    bool started_ = false;
    // function
    std::function<void()> script_;
};

}//end of utility namespace

#endif // TIMER_H_INCLUDED
