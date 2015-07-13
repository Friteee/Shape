#ifndef OBJECT_STATE_H_INCLUDED
#define OBJECT_STATE_H_INCLUDED

namespace game
{

class Object_state
{
public:
    virtual void update() = 0;
    virtual void show(int x, int y) = 0;
    virtual void get_in() = 0;
    virtual void get_out() = 0;
    virtual ~Object_state(){}
private:
    Moving_object * object_;
};

}

#endif // OBJECT_STATE_H_INCLUDED
