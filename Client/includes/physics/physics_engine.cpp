#include "physics_engine.h"
#include "../utility/stopwatch.h"
#include <chrono>

namespace physics
{


/** \brief add static object for collision detection
 *
 * \param Polygon * added - geometrical polygon to get added
 *
 */

void Physics_engine::add_static_object(Polygon * added)
{
    objects_change_.lock();

    Static_command buffer;
    buffer.set(added);
    static_addition_.push_back(buffer);

    objects_change_.unlock();
}

/** \brief add moving objects for collision detection and detected collision handling
 *
 * \param Polygon * added - geometrical polygon to get added
 *
 */

void Physics_engine::add_moving_object(Physics_component * added)
{
    objects_change_.lock();

    Moving_command buffer;
    buffer.set(added);
    moving_addition_.push_back(buffer);

    objects_change_.unlock();
}

/** \brief deletion of a static object
 *
 * \param Polygon * deleted - geometrical polygon to get deleted
 *
 *  WARNING - performance cost of O(n)
 */


void Physics_engine::delete_static_object(Polygon * deleted)
{
    objects_change_.lock();

    Static_command buffer;
    buffer.set(deleted);
    static_deletion_.push_back(buffer);

    objects_change_.unlock();
}


/** \brief deletion of a moving object
 *
 * \param Polygon * deleted - geometrical polygon to get deleted
 *
 *  WARNING - performance cost of O(n)
 */
void Physics_engine::delete_moving_object(Physics_component * deleted)
{
    objects_change_.lock();

    Moving_command buffer;
    buffer.set(deleted);
    moving_deletion_.push_back(buffer);

    objects_change_.unlock();
}
/** \brief Physics run function to detect collisions, apply speed, change position and etc.
 *
 *
 *  Call it only once.
 *  Potentially thread-safe.
 *  Potential algorithm complexity - O(m*n*l + m^2) , where m - moving objects, n - static objects, l - points in moving objects geometry
 */
void Physics_engine::run(unsigned int ticks)
{
    ticks_per_second_ = ticks;
    stop_ = false;
    engine_ = new std::thread (&Physics_engine::thread , this);

}

/** \brief Check for object addition to physics
 *
 *
 */

void Physics_engine::check_addition()
{
    objects_change_.lock();

    Polygon * buffer;
    Physics_component * buffer_component;
    while(!moving_addition_.empty())
    {
        buffer_component = moving_addition_.front().get();
        moving_addition_.pop_front();
        moving_objects_.push_back(buffer_component);
    }
    while(!static_addition_.empty())
    {
        buffer = static_addition_.front().get();
        static_addition_.pop_front();
        static_objects_.push_back(buffer);
    }
    while(!static_deletion_.empty())
    {
        buffer = static_deletion_.front().get();
        static_deletion_.pop_front();
        for(int a = 0, b = static_objects_.size(); a<b; a++)
        {
            if(static_objects_[a] == buffer)
            {
                static_objects_.erase(static_objects_.begin() + a);
                break;
            }
        }
    }
    while(!moving_deletion_.empty())
    {
        buffer_component = moving_deletion_.front().get();
        moving_deletion_.pop_front();
        for(int a = 0, b = moving_objects_.size(); a < b; a++)
        {
            if(moving_objects_[a] == buffer_component)
            {
                moving_objects_.erase(moving_objects_.begin() + a);
                break;
            }
        }
    }
    objects_change_.unlock();

    //todo
}


/** \brief Reset all objects
 *
 *  Could block caller for 1 to 16 milliseconds
 */

void Physics_engine::reset()
{
    stop_ = true;
    engine_->join();
    delete engine_;

    moving_addition_.clear();
    moving_deletion_.clear();
    static_addition_.clear();
    static_deletion_.clear();
    moving_objects_.clear();
    static_objects_.clear();
}


void Physics_engine::update_moving()
{
    //update
    for(unsigned int a = 0; a < moving_objects_.size() ; a++)
    {
        moving_objects_[a]->update(ticks_per_second_);
    }
}

void Physics_engine::check_collision()
{
    //check and notify collisions for moving - static objects
    for(unsigned int a = 0 , a_size = moving_objects_.size() ; a < a_size ; a++)
    {
        const Polygon & buffer = moving_objects_[a]->get_polygon();
        const std::vector<SDL_Point>& points = buffer.get_points();
        for(unsigned int b = 0 , b_size = points.size() ; b < b_size ; b++)
        {
            for(unsigned int c = 0 , c_size = static_objects_.size() ; c < c_size; c++)
            {
                if(static_objects_[c]->is_inside(points[b]))
                {
                    moving_objects_[a]->notify_static(b);
                }
            }
        }
    }
    //check and notify collisions for moving - moving objects
    for(unsigned int a = 0 , a_size = moving_objects_.size() ; a < a_size ; a++)
    {
        const Polygon & buffer = moving_objects_[a]->get_polygon();
        const std::vector<SDL_Point>& points = buffer.get_points();
        for(unsigned int b = 0 , b_size = points.size() ; b < b_size ; b++)
        {
            for(unsigned int c = 0 , c_size = moving_objects_.size() ; c < c_size; c++)
            {
                if(a==c)
                    continue;
                else if(moving_objects_[c]->get_polygon().is_inside(points[b]))
                {
                    moving_objects_[a]->notify_moving(moving_objects_[b]);
                    moving_objects_[b]->notify_moving(moving_objects_[a]);
                }
            }
        }
    }
}

void Physics_engine::thread()
{
    utility::Stopwatch ticks;
    ticks.start();

    while(!stop_)
    {

        check_addition();

        update_moving();

        check_collision();

        if(ticks.get_ticks() < 1000.f / ticks_per_second_ && !stop_)
        {
            std::chrono::milliseconds duration = std::chrono::milliseconds(1000 / ticks_per_second_ - ticks.get_ticks());
            std::this_thread::sleep_for(duration);
        }

        ticks.reload();

    }

}


Polygon * Physics_engine::Static_command::get()
{
    return object_;
}

void Physics_engine::Static_command::set(Polygon * added)
{
    object_ = added;
}

Physics_component * Physics_engine::Moving_command::get()
{
    return object_;
}

void Physics_engine::Moving_command::set(Physics_component * added)
{
    object_ = added;
}

}
