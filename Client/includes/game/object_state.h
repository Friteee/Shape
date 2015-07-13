#ifndef OBJECT_STATE_H_INCLUDED
#define OBJECT_STATE_H_INCLUDED

namespace game
{

class Object_state
{
public:
    virtual void update();
    virtual void show();
    virtual ~Object_state(){}
private:
    Moving_object * object;
};

}

#endif // OBJECT_STATE_H_INCLUDED
