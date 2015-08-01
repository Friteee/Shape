#ifndef FALLING_OBJECT_PHYSICS_H_INCLUDED
#define FALLING_OBJECT_PHYSICS_H_INCLUDED

#include "physics_component.h"
#include <SDL.h>

namespace physics
{

class Falling_object_physics : public Physics_component
{
public:
    Falling_object_physics(float init_gravity, SDL_Point init_location);

    virtual void update(unsigned int time) override;

    virtual void notify_static(unsigned int point , game::Static_object * object)override;

    virtual void notify_moving(Physics_component* moving) override;

    virtual SDL_Point get_interpolated_location(unsigned int time) override;

    void set_horizontal_acceleration(float init_acceleration);

private:
    float horizontal_acceleration_;
    float gravity_;
    float x_ , y_;
    float previous_x_ , previous_y_;
    float x_speed_, y_speed_;

};

}

#endif // PLAYER_PHYSICS_H_INCLUDED
