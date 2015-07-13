
#include "gaming_mode.h"
#include "main_menu_mode.h"
#include "game_logic.h"
#include "../gui/progress_bar.h"
#include "../gui/click.h"
#include "../audio/music.h"
#include "../game/moving_object.h"

#include <cstdlib>
#include <sstream>

namespace main_logic
{

/**
 * Gaming mode's input handler
 */

bool Gaming_mode::handle_input()
{
    gui::Click click;
    click.set_clicked(false);
    while(SDL_PollEvent(&event_))
    {
        switch(event_.type)
        {
        case SDL_QUIT:
            return false;
            break;
        case SDL_KEYDOWN:
            switch(event_.key.keysym.sym)
            {
            case SDLK_q:
                break;
            case SDLK_a:
                break;
            case SDLK_w:
                break;
            case SDLK_s:
                break;
            case SDLK_d:
                break;
            case SDLK_RALT:
                break;
            case SDLK_LALT:
                break;
            case SDLK_TAB:
                break;
            case SDLK_BACKSPACE:
                break;
            case SDLK_ESCAPE:
                main_logic::Game_logic::set_current_mode( new Main_menu_mode (main_config_) );
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            click.set_clicked(false);
            if(event_.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event_.button.x,event_.button.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            click.set_clicked(true);
            if(event_.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event_.button.x,event_.button.y);
            }
            break;
        case SDL_WINDOWEVENT:
            switch(event_.window.event)
            {
            case SDL_WINDOWEVENT_EXPOSED:
                break;
            case SDL_WINDOWEVENT_MOVED:
                break;
            }
            break;
        case SDL_MOUSEWHEEL:
            break;
        case SDL_TEXTINPUT:
            break;

        }
    }


    const Uint8 * key_states =SDL_GetKeyboardState(nullptr);

    // if alt + tab was pressed
    if((key_states[SDL_SCANCODE_LALT]||key_states[SDL_SCANCODE_RALT])&&key_states[SDL_SCANCODE_TAB])
    {
        // minimize the window
        video::Video_subsystem::minimize();
    }

    return true;
}

/**
 * Gaming mode's game loop
 */

bool Gaming_mode::run()
{

    // handle that input
    if(handle_input()==false)
    {
        return false;
    }
    // reload video subsystem
    video::Video_subsystem::reload();

    gui_manager_.update();

    // main logic here
    main_background_.show();

    gui_manager_.show();

    video::Video_subsystem::update_screen();

    return true;
}

/**
 * Constructor
 */

Gaming_mode::Gaming_mode(utility::Configuration * init_config ):
    main_config_(init_config)
{
    // background
    main_background_.change_image(main_config_->find_string("game_background").c_str());
}


}//end of main_logic namespace
