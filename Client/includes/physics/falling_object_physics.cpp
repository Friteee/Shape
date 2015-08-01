
#include "falling_object_physics.h"

namespace physics
{

Falling_object_physics::Falling_object_physics(float init_gravity, SDL_Point init_location)
{
    horizontal_acceleration_ = 0;
    gravity_ = init_gravity;
    x_ = init_location.x;
    y_ = init_location.y;
    x_speed_ = 0;
    y_speed_ = 0;
}

void Falling_object_physics::update(unsigned int time)
{
    previous_x_ = x_;
    previous_y_ = y_;
    float seconds = static_cast<float>(time) / 1000;
    x_ = x_speed_ * seconds + horizontal_acceleration_ * seconds * seconds / 2;
    y_ = y_speed_ * seconds + gravity_ * seconds * seconds / 2;
    x_speed_ += horizontal_acceleration_ * seconds;
    y_speed_ += gravity_ * seconds;
}

void Falling_object_physics::notify_static(unsigned int collided_point , game::Static_object * object)
{
    if(object->get_tile_type()->get_invincibility())
    {
        return;
    }

    auto points = polygon_->get_points();

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
        x_ = previous_x_;
        x_speed_ = 0;
    }

    if(points[collided_point].x == rightmost)
    {
        x_ = previous_x_;
        x_speed_ = 0;
    }

    if(points[collided_point].y == topmost)
    {
        y_ = previous_y_;
        y_speed_ = -y_speed_;
    }

    if(points[collided_point].y == bottommost)
    {
        y_ = previous_y_;
        y_speed_ = 0;
    }

}

void Falling_object_physics::notify_moving(Physics_component* moving)
{

}

SDL_Point Falling_object_physics::get_interpolated_location(unsigned int time)
{
    SDL_Point location;
    float seconds = float(time) / 1000;
    if(y_speed_ != 0)
    {
        location.y = static_cast<int>(y_ + y_speed_ * seconds + gravity_ * seconds * seconds / 2);
    }
    if(x_speed_ != 0)
    {
        location.x = static_cast<int>(x_ + x_speed_ * seconds + horizontal_acceleration_ * seconds * seconds / 2);
    }
    return location;
}

void Falling_object_physics::set_horizontal_acceleration(float init_acceleration)
{
    horizontal_acceleration_ = init_acceleration;
}

}
