#ifndef AI_COMPONENT_H_INCLUDED
#define AI_COMPONENT_H_INCLUDED

namespace ai
{

/** \brief Base class for handling objects current state
 *
 *  State could range from jumping to sprinting or exploding and etc..
 *  Should be deleted by moving object
 */

class AI_component
{
public:
    virtual void update() = 0;

    void init(game::Moving_object * init_object)
    {
        init_object = object;
    }

private:
    // associated moving object
    game::Moving_object * object;

};

}//end of ai namespace

#endif // AI_COMPONENT_H_INCLUDED
