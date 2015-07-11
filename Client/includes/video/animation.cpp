
#include "animation.h"


namespace video
{

void Animation::reset()
{
    current_ = 0;
    frame_stopwatch_.stop();
}

void Animation::start()
{
    current_ = 0;
    frame_stopwatch_.start();
}

void Animation::add_frame(std::string filename , int time)
{
    Texture buffer;
    buffer.init(filename);
    frames_.push_back(buffer);
    ms_per_frame_.push_back(time);
}

void Animation::add_frame(Texture & added , int time)
{
    frames_.push_back(added);
    ms_per_frame_.push_back(time);
}

void Animation::delete_current()
{
    frames_.erase(frames_.begin() + current_);
}

Texture & Animation::get_current()
{
    if(frame_stopwatch_.get_ticks() > ms_per_frame_[current_] ) // new frame ?
    {
        frame_stopwatch_.reload();
        current_ != (frames_.size()-1) ? current_++ : current_ = 0; // loop around
    }
    return frames_[current_];
}

} // end of video namespace
