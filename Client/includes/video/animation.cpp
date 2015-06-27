
#include "animation.h"


namespace video
{

void Animation::reset()
{
    current = 0;
    frame_stopwatch.stop();
}

void Animation::start()
{
    current = 0;
    frame_stopwatch.start();
}

void Animation::add_frame(std::string filename , int time)
{
    Texture buffer;
    buffer.init(filename);
    frames.push_back(buffer);
    ms_per_frame.push_back(time);
}

void Animation::add_frame(Texture & added , int time)
{
    frames.push_back(added);
    ms_per_frame.push_back(time);
}

void Animation::delete_current()
{
    frames.erase(frames.begin() + current);
}

Texture & Animation::get_current()
{
    if(frame_stopwatch.get_ticks() > ms_per_frame[current] ) // new frame ?
    {
        frame_stopwatch.reload();
        current != (frames.size()-1) ? current++ : current = 0; // loop around
    }
    return frames[current];
}

} // end of video namespace
