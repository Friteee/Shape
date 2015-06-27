
#include "falling_object_physics.h"

namespace physics
{

Falling_object_physics::Falling_object_physics(float init_gravity, SDL_Point init_location)
{
    horizontal_acceleration = 0;
    gravity = init_gravity;
    x = init_location.x;
    y = init_location.y;
    x_speed = 0;
    y_speed = 0;
}

void Falling_object_physics::update(unsigned int time)
{
    previous_x = x;
    previous_y = y;
    float seconds = float(time) / 1000;
    x = x_speed * seconds + horizontal_acceleration * seconds * seconds / 2;
    y = y_speed * seconds + gravity * seconds * seconds / 2;
    x_speed += horizontal_acceleration * seconds;
    y_speed += gravity * seconds;
}

void Falling_object_physics::notify_static(unsigned int collided_point)
{
    auto points = polygon->get_points();

    int leftmost = points[0].x;
    int rightmost = points[0].x;
    int topmost = points[0].y;
    int bottommost = points[0].y;

    for(auto point: points)
    {
        if(point.x < leftmost)
        {
            leftmost = point.x;
        }
        if(point.x > rightmost)
        {
            rightmost = point.x;
        }
        if(point.y < topmost)
        {
            topmost = point.y;
        }
        if(point.y > bottommost)
        {
            bottommost = point.y;
        }
    }

    // is this point on top, bottom or left or right?
    if(points[collided_point].x == leftmost)
    {
        x = previous_x;
        x_speed = 0;
    }

    if(points[collided_point].x == rightmost)
    {
        x = previous_x;
        x_speed = 0;
    }

    if(points[collided_point].y == topmost)
    {
        y = previous_y;
        y_speed = -y_speed;
    }

    if(points[collided_point].y == bottommost)
    {
        y = previous_y;
        y_speed = 0;
    }

}

void Falling_object_physics::notify_moving(Physics_component* moving)
{

}

SDL_Point Falling_object_physics::get_interpolated_location(unsigned int time)
{
    SDL_Point location;
    float seconds = float(time) / 1000;
    if(y_speed != 0)
    {
        location.y = static_cast<int>(y + y_speed * seconds + gravity * seconds * seconds / 2);
    }
    if(x_speed != 0)
    {
        location.x = static_cast<int>(x + x_speed * seconds + horizontal_acceleration * seconds * seconds / 2);
    }
    return location;
}

void Falling_object_physics::set_horizontal_acceleration(float init_acceleration)
{
    horizontal_acceleration = init_acceleration;
}

}
