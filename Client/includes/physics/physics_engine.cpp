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
    objects_change.lock();

    Static_command buffer;
    buffer.set(added);
    static_addition.push_back(buffer);

    objects_change.unlock();
}

/** \brief add moving objects for collision detection and detected collision handling
 *
 * \param Polygon * added - geometrical polygon to get added
 *
 */

void Physics_engine::add_moving_object(Physics_component * added)
{
    objects_change.lock();

    Moving_command buffer;
    buffer.set(added);
    moving_addition.push_back(buffer);

    objects_change.unlock();
}

/** \brief deletion of a static object
 *
 * \param Polygon * deleted - geometrical polygon to get deleted
 *
 *  WARNING - performance cost of O(n)
 */


void Physics_engine::delete_static_object(Polygon * deleted)
{
    objects_change.lock();

    Static_command buffer;
    buffer.set(deleted);
    static_deletion.push_back(buffer);

    objects_change.unlock();
}


/** \brief deletion of a moving object
 *
 * \param Polygon * deleted - geometrical polygon to get deleted
 *
 *  WARNING - performance cost of O(n)
 */
void Physics_engine::delete_moving_object(Physics_component * deleted)
{
    objects_change.lock();

    Moving_command buffer;
    buffer.set(deleted);
    moving_deletion.push_back(buffer);

    objects_change.unlock();
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
    ticks_per_second = ticks;
    stop = false;
    engine = new std::thread (&Physics_engine::thread , this);

}

/** \brief Check for object addition to physics
 *
 *
 */

void Physics_engine::check_addition()
{
    objects_change.lock();

    Polygon * buffer;
    Physics_component * buffer_component;
    while(!moving_addition.empty())
    {
        buffer_component = moving_addition.front().get();
        moving_addition.pop_front();
        moving_objects.push_back(buffer_component);
    }
    while(!static_addition.empty())
    {
        buffer = static_addition.front().get();
        static_addition.pop_front();
        static_objects.push_back(buffer);
    }
    while(!static_deletion.empty())
    {
        buffer = static_deletion.front().get();
        static_deletion.pop_front();
        for(int a = 0, b = static_objects.size(); a<b; a++)
        {
            if(static_objects[a] == buffer)
            {
                static_objects.erase(static_objects.begin() + a);
                break;
            }
        }
    }
    while(!moving_deletion.empty())
    {
        buffer_component = moving_deletion.front().get();
        moving_deletion.pop_front();
        for(int a = 0, b = moving_objects.size(); a < b; a++)
        {
            if(moving_objects[a] == buffer_component)
            {
                moving_objects.erase(moving_objects.begin() + a);
                break;
            }
        }
    }
    objects_change.unlock();

    //todo
}


/** \brief Reset all objects
 *
 *  Could block caller for 1 to 16 milliseconds
 */

void Physics_engine::reset()
{
    stop = true;
    engine->join();
    delete engine;

    moving_addition.clear();
    moving_deletion.clear();
    static_addition.clear();
    static_deletion.clear();
    moving_objects.clear();
    static_objects.clear();
}


void Physics_engine::update_moving()
{
    //update
    for(unsigned int a = 0; a < moving_objects.size() ; a++)
    {
        moving_objects[a]->update(ticks_per_second);
    }
}

void Physics_engine::check_collision()
{
    //check and notify collisions for moving - static objects
    for(unsigned int a = 0 , a_size = moving_objects.size() ; a < a_size ; a++)
    {
        const Polygon & buffer = moving_objects[a]->get_polygon();
        const std::vector<SDL_Point>& points = buffer.get_points();
        for(unsigned int b = 0 , b_size = points.size() ; b < b_size ; b++)
        {
            for(unsigned int c = 0 , c_size = static_objects.size() ; c < c_size; c++)
            {
                if(static_objects[c]->is_inside(points[b]))
                {
                    moving_objects[a]->notify_static(b);
                }
            }
        }
    }
    //check and notify collisions for moving - moving objects
    for(unsigned int a = 0 , a_size = moving_objects.size() ; a < a_size ; a++)
    {
        const Polygon & buffer = moving_objects[a]->get_polygon();
        const std::vector<SDL_Point>& points = buffer.get_points();
        for(unsigned int b = 0 , b_size = points.size() ; b < b_size ; b++)
        {
            for(unsigned int c = 0 , c_size = moving_objects.size() ; c < c_size; c++)
            {
                if(a==c)
                    continue;
                else if(moving_objects[c]->get_polygon().is_inside(points[b]))
                {
                    moving_objects[a]->notify_moving(moving_objects[b]);
                    moving_objects[b]->notify_moving(moving_objects[a]);
                }
            }
        }
    }
}

void Physics_engine::thread()
{
    utility::Stopwatch ticks;
    ticks.start();

    while(!stop)
    {

        check_addition();

        update_moving();

        check_collision();

        if(ticks.get_ticks() < 1000.f / ticks_per_second && !stop)
        {
            std::chrono::milliseconds duration = std::chrono::milliseconds(1000 / ticks_per_second - ticks.get_ticks());
            std::this_thread::sleep_for(duration);
        }

        ticks.reload();

    }

}


Polygon * Physics_engine::Static_command::get()
{
    return object;
}

void Physics_engine::Static_command::set(Polygon * added)
{
    object = added;
}

Physics_component * Physics_engine::Moving_command::get()
{
    return object;
}

void Physics_engine::Moving_command::set(Physics_component * added)
{
    object = added;
}

}
