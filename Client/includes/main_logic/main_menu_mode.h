#ifndef MAIN_MENU_MODE_H_INCLUDED
#define MAIN_MENU_MODE_H_INCLUDED

#include "program_mode.h"
#include "../gui/text_button.h"
#include "../gui/gui_manager.h"
#include "../gui/background.h"
#include "../gui/button.h"
#include "../audio/music.h"



namespace main_logic
{

/**
 * \brief Main menu
 *
 * Handles clicks, has play and options buttons and etc.
 */

class Main_menu_mode : public Program_mode
{
public :

    Main_menu_mode(utility::Configuration * init_config);
    bool       run ()override;
    bool       handle_input()override;

private:

    // main configuration
    utility::Configuration * main_config_;
    // event
    SDL_Event                event_;
    // gui manager
    gui::Gui_manager         main_gui_;
    //background
    gui::Background          background_;
    // quit
    bool                     quit_;
};

} // end of main_logic namespace

#endif // EDITOR_MODE_H_INCLUDED
