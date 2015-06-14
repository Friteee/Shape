#ifndef PHYSICS_ENGINE_H_INCLUDED
#define PHYSICS_ENGINE_H_INCLUDED

#include "geometry.h"
#include "physics_component.h"
#include <vector>
#include <mutex>
#include <list>

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
    void add_static_object(Geometry * added);
    void add_moving_object(Physics_component * added);
    void delete_static_object(Geometry * deleted);
    void delete_moving_object(Physics_component * deleted);
    void run();
    void reset();
private:
    void check_addition();

    class Static_command
    {
    public:
        Geometry * get();
        void set(Geometry * added);
    private:
        Geometry * object;
    };

    class Moving_command
    {
    public:
        Physics_component * get();
        void set(Physics_component * added);
    private:
        Physics_component * object;
    };

    std::vector<Geometry *> static_objects;
    std::vector<Physics_component *> moving_objects;
    std::mutex objects_change;
    std::list <Static_command> static_addition;
    std::list <Moving_command> moving_addition;
    std::list <Static_command> static_deletion;
    std::list <Moving_command> moving_deletion;





};



}

#endif // PHYSICS_ENGINE_H_INCLUDED
