#include "physics_engine.h"

namespace physics
{


/** \brief add static object for collision detection
 *
 * \param Geometry * added - geometrical polygon to get added
 *
 */

void Physics_engine::add_static_polygon(Geometry * added)
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

void Physics_engine::add_moving_polygon(Geometry * added)
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


void Physics_engine::delete_static_polygon(Geometry * deleted)
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
void Physics_engine::delete_moving_polygon(Geometry * deleted)
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
 *  Call it only once
 *  Potentially thread-safe
 */
void Physics_engine::run()
{
    objects_change.lock();

    Geometry * buffer;
    while(!moving_addition.empty())
    {
        buffer = moving_addition.front().get();
        moving_addition.pop_front();
        moving_objects.push_back(buffer);
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
        buffer = moving_deletion.front().get();
        moving_deletion.pop_front();
        for(int a = 0, b = moving_objects.size(); a < b; a++)
        {
            if(moving_objects[a] == buffer)
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

Geometry * Physics_engine::Moving_command::get()
{
    return object;
}

void Physics_engine::Moving_command::set(Geometry * added)
{
    object = added;
}

}
