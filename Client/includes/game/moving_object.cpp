
#include "moving_object.h"

namespace game
{


Moving_object::Moving_object(physics::Physics_component * init_physics, ai::AI_component * init_AI, video::Render_component * init_render)
{
    physics_component = init_physics;
    AI = init_AI;
    render = init_render;
}



}
