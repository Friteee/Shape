#ifndef RENDER_COMPONENT_H_INCLUDED
#define RENDER_COMPONENT_H_INCLUDED

namespace video
{

class Render_component
{
public:
    virtual void show() = 0;
    void init_object (game::Moving_object * init_object)
    {
        object = init_object;
    }
private:
    game::Moving_object * object;
};

}

#endif // RENDER_COMPONENT_H_INCLUDED
