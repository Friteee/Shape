#include "physics_engine.h"

namespace physics
{


/** \brief add static object for collision detection
 *
 * \param Geometry * added - geometrical polygon to get added
 *
 */

void Physics_engine::add_static_object(Geometry * added)
{
    objects_change.lock();

    Static_command buffer;
    buffer.set(added);
    static_addition.push_back(buffer);

    objects_change.unlock();
}

/** \brief add moving objects for collision detection and detected collision handling
 *
 * \param Geometry * added - geometrical polygon to get added
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
 * \param Geometry * deleted - geometrical polygon to get deleted
 *
 *  WARNING - performance cost of O(n)
 */


void Physics_engine::delete_static_object(Geometry * deleted)
{
    objects_change.lock();

    Static_command buffer;
    buffer.set(deleted);
    static_deletion.push_back(buffer);

    objects_change.unlock();
}


/** \brief deletion of a moving object
 *
 * \param Geometry * deleted - geometrical polygon to get deleted
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
void Physics_engine::run()
{
    check_addition();

    //update
    for(unsigned int a = 0; a < moving_objects.size() ; a++)
    {
        moving_objects[a]->update();
    }

    //check and notify collisions
    for(unsigned int a = 0 , a_size = moving_objects.size() ; a < a_size ; a++)
    {
        Geometry * buffer = moving_objects[a]->get_polygon();
        std::vector<SDL_Point>& points = buffer->get_points();
        for(unsigned int b = 0 , b_size = points.size() ; b < b_size ; b++)
        {
            for(unsigned int c = 0 , c_size = static_objects.size() ; c < c_size; c++)
            {
                if(static_objects[c]->is_inside(points[b]))
                {
                    moving_objects[a]->notify(points[b]);
                }
            }
        }
    }
}

/** \brief Check for object addition to physics
 *
 *
 */

void Physics_engine::check_addition()
{
    objects_change.lock();

    Geometry * buffer;
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
 *
 */

void Physics_engine::reset()
{
    moving_objects.clear();
    static_objects.clear();
}


Geometry * Physics_engine::Static_command::get()
{
    return object;
}

void Physics_engine::Static_command::set(Geometry * added)
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
