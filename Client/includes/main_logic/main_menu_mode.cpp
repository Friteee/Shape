
#include <cstdio>
#include <cmath>
#include "main_menu_mode.h"
#include "gaming_mode.h"
#include "game_logic.h"
#include "../gui/click.h"
#include "../gui/button.h "



namespace main_logic
{

/**
 * Running mode
 * Returns false if user wants to quit
 */

bool Main_menu_mode::run()
{

    if(handle_input()==false || quit == true)
    {
        return false;
    }
    video::Video_subsystem::reload();

    //update
    main_gui.update();


    //show
    background.show();
    main_gui.show();

    video::Video_subsystem::update_screen();

    return true;
}

/**
 * Input handling.
 * Used mostly to move the grid
 * Returns false if user wants to quit
 */

bool Main_menu_mode::handle_input()
{
    gui::Click click;
    click.set_clicked(false);
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            return false;
            music.stop();
            break;
        case SDL_MOUSEBUTTONDOWN:
            click.set_clicked(false);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event.button.x,event.button.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            click.set_clicked(true);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                click.set_location(event.button.x,event.button.y);
            }
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_r:
                break;
            case SDLK_ESCAPE:
                return false;
                break;
            case SDLK_q:
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEWHEEL:
            break;
        default:
            break;
        }
    }
    const Uint8 * key_strokes = SDL_GetKeyboardState(nullptr);
    if((key_strokes[SDL_SCANCODE_RALT]||key_strokes[SDL_SCANCODE_LALT])&&key_strokes[SDL_SCANCODE_TAB])
    {
        video::Video_subsystem::minimize();
    }

    return true;
}

/**
 * Editor constructor
 */

Main_menu_mode::Main_menu_mode(utility::Configuration * init_config) :
    main_config(init_config),
    grid_speed(atoi(main_config->find_string("grid_speed").c_str())),
    grid_x(0),
    grid_y(0),
    change_mode(false),
    quit(false)
{

    // background
    background.change_image(main_config->find_string("main_background").c_str());

}

}//end of main_logic namespace

