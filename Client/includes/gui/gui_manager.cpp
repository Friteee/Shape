

#include "gui_manager.h"
#include "click.h"
#include <cstdio>

namespace gui
{

Gui_manager::Gui_manager()
{

}

Gui_manager::~Gui_manager()
{
    for(auto & a : elements_)
    {
        delete a;
    }
}

void Gui_manager::add_element(Gui_element * added_element)
{
    elements_.push_back(added_element);
}

void Gui_manager::update()
{
    gui::Click click;
    for(int a = 0, b = elements_.size() ; a < b ; ++a)
    {
        if(elements_[a]->is_deleted())
        {
            delete elements_[a];
            elements_.erase(elements_.begin()+a);
            a--;
            b--;
            continue;
        }

        if(click.has_clicked())
        {
            int x , y;
            click.get_location(x,y);
            elements_[a]->handle_click(x,y);
        }
        elements_[a]->update();

    }
}

void Gui_manager::show()
{
    for(auto & a : elements_)
    {
        a->show();
    }
}
}//end of gui namespace
