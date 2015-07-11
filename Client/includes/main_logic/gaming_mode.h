#ifndef GAMING_MODE_H_INCLUDED
#define GAMING_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/background.h"
#include "../gui/gui_manager.h"
#include "../video/texture.h"
#include "../gui/text.h"
#include "../audio/music.h"
#include <string>

namespace main_logic
{

/** \brief Main mode for game itself
 * Here is the game itself
 */



class Gaming_mode : public Program_mode
{
public :

    Gaming_mode(utility::Configuration * init_config );
    bool       run ()override;
    bool       handle_input()override;

private:
    gui::Background          main_background_;
    // event
    SDL_Event                event_;
    // configuration
    utility::Configuration * main_config_;
    // gui elements manager
    gui::Gui_manager         gui_manager_;


};

}

#endif // GAMING_MODE_H_INCLUDED
