#ifndef MOVING_OBJECT_H_INCLUDED
#define MOVING_OBJECT_H_INCLUDED

namespace game
{
    class Moving_object;
}
namespace physics
{
    class Physics_component;
}

enum Object_type
{
    PLAYER, BULLET
};

#include "object_command.h"
#include "../physics/physics_component.h"
#include "../ai/ai_component.h"
#include "../video/render_component.h"

namespace game
{

/** \brief Base class for moving objects
 *
 * Objects, which are not part of the scenery, like player or pickups
 *
 */

class Moving_object
{
public:
    virtual void notify(Object_command * command) = 0;
    Moving_object(physics::Physics_component * init_physics, ai::AI_component * init_AI, video::Render_component * init_render);
private:
    physics::Physics_component * physics_component;
    ai::AI_component           * AI;
    video::Render_component    * render;
    Object_command             * first;
};

}// end of gamer namespace

#endif // MOVING_OBJECT_H_INCLUDED
