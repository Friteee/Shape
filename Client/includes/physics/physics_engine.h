#ifndef PHYSICS_ENGINE_H_INCLUDED
#define PHYSICS_ENGINE_H_INCLUDED

#include "polygon.h"
#include "physics_component.h"
#include <vector>
#include <mutex>
#include <list>
#include <thread>
#include <atomic>

namespace physics
{


/** \class physics::Physics_engine
 *
 * \brief Class used for collision detection and physical objects updates
 *
 * One uses add_static_polygon to add static objects for collision detection,
 * add_moving_polygon to add moving objects for collision detection and detected collision handling,
 * delete_static_polygon to delete a static object
 * delete_moving_polygon to delete a moving object
 * run to handle collisions and run physics calculations
 * reset to delete every physics object (both static and moving) from collision detection
 */

class Physics_engine
{

public:

    void add_static_object(Polygon * added);
    void add_moving_object(Physics_component * added);
    void delete_static_object(Polygon * deleted);
    void delete_moving_object(Physics_component * deleted);
    void run(unsigned int ticks_per_s);
    void reset();

private:
    void check_addition();
    void update_moving();
    void check_collision();
    void thread();

    class Static_command
    {
    public:
        Polygon * get();
        void set(Polygon * added);
    private:
        Polygon * object;
    };

    class Moving_command
    {
    public:
        Physics_component * get();
        void set(Physics_component * added);
    private:
        Physics_component * object;
    };

    std::vector<Polygon *>           static_objects;
    std::vector<Physics_component *> moving_objects;
    std::mutex                       objects_change;
    std::list <Static_command>       static_addition;
    std::list <Moving_command>       moving_addition;
    std::list <Static_command>       static_deletion;
    std::list <Moving_command>       moving_deletion;
    std::thread                    * engine;
    std::atomic_bool                 stop ;
    unsigned int                     ticks_per_second;





};



}

#endif // PHYSICS_ENGINE_H_INCLUDED
