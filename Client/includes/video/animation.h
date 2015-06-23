#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <string>
#include <vector>
#include "texture.h"
#include "../utility/stopwatch.h"

namespace video
{

/** \brief Animation for objects
 *
 * Holder class for frames of the animation
 */


class Animation
{
public:
    void      reset();
    void      start();
    void      add_frame(std::string filename , int time);
    void      delete_current();
    Texture & get_current();
private:
    std::vector<Texture>          frames;
    std::vector<unsigned int>     ms_per_frame;
    utility::Stopwatch            frame_stopwatch;
    bool                          running;
    unsigned int                  current;
};

}

#endif // ANIMATION_H_INCLUDED
