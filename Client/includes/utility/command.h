#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

namespace utility
{

class Command
{
public:
    virtual void execute() = 0;
    virtual void redo() = 0;
};

}

#endif // COMMAND_H_INCLUDED
