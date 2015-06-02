#ifndef GAMING_MODE_H_INCLUDED
#define GAMING_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/background.h"
#include "../gui/gui_manager.h"
#include "../video/texture.h"
#include "../gui/text.h"
#include "../audio/sound.h"
#include "../utility/stopwatch.h"
#include "../audio/music.h"

namespace gui
{
class Progress_bar;
}

#include <string>

namespace main_logic
{

class Gaming_mode : public Program_mode
{
public :

    Gaming_mode(utility::Configuration * init_config );
    bool run ()override;
    bool handle_input()override;

private:
    gui::Background        * main_background;
    // event
    SDL_Event                event;
    // configuration
    utility::Configuration * main_config;
    // gui elements manager
    gui::Gui_manager         gui_manager;


};

}

#endif // GAMING_MODE_H_INCLUDED
