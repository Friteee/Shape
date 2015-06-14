#ifndef OBJECT_COMMAND_H_INCLUDED
#define OBJECT_COMMAND_H_INCLUDED

#include "moving_object.h"

namespace game
{

/** \brief Base class for command, executed on object
 *
 *  Every derived class should implement execute, redo
 *  and initialize time stamp in constructor as SDL_GetTicks().
 *  They should be deleted by the object itself
 */

class Object_command
{
public:
    virtual void execute(Moving_object * object) = 0;
    virtual void redo(Moving_object * object) = 0;
    Object_command * get_next()
    {
        return next;
    }
    Object_command * get_previous()
    {
        return next;
    }
    unsigned int get_time()
    {
        return timestamp;
    }
private:
    unsigned int timestamp;
    Object_command * next;
    Object_command * previous;
};

}

#endif // OBJECT_COMMAND_H_INCLUDED
