#ifndef GUI_ELEMENT_H_INCLUDED
#define GUI_ELEMENT_H_INCLUDED

#include <SDL.h>
#include "../video/texture.h"

namespace gui
{

/**
 * \brief Gui element base class
 *
 * Gui element base class.
 * Its' derived classes could range from buttons to health bar
 */

class Gui_element
{
public:

    virtual void show() = 0;
    virtual void update() = 0;
    virtual void handle_click(int x, int y)= 0 ;

    //inline functions

    inline void hide()
    {
        visible_ = false;
    }
    inline void unhide()
    {
        visible_ = true;
    }
    inline bool get_visibility()
    {
        return visible_;
    }
    inline void set_for_deletion()
    {
        marked_for_deletion_=true;
    }
    inline bool is_deleted()
    {
        return marked_for_deletion_;
    }
    inline void change_position(int x, int y)
    {
        location_.x=x;
        location_.y=y;
    }
    inline int get_width()
    {
        return location_.w;
    }
    inline int get_height()
    {
        return location_.h;
    }
    inline void set_width(int width)
    {
        location_.w = width;
    }
    inline void set_height(int height)
    {
        location_.h = height;
    }
    virtual ~Gui_element() {}

protected :

    SDL_Rect       location_;
    video::Texture texture_;
    bool           visible_,
                   marked_for_deletion_ = false;

};

}//end of object namespace

#endif // GUI_ELEMENT_H_INCLUDED
