#ifndef OBJECT_COMMAND_H_INCLUDED
#define OBJECT_COMMAND_H_INCLUDED

namespace game
{

class Moving_object;

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
    virtual void redo   (Moving_object * object) = 0;
    virtual ~Object_command(){}
    Object_command *& get_next()
    {
        return next_;
    }
    Object_command *& get_previous()
    {
        return previous_;
    }
    unsigned int get_time()
    {
        return timestamp_;
    }
    void set_timestamp( unsigned int set_time)
    {
        timestamp_ = set_time;
    }
protected:
    unsigned int timestamp_;
    Object_command * next_;
    Object_command * previous_;
};

}

#endif // OBJECT_COMMAND_H_INCLUDED
