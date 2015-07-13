
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

    if(handle_input()==false || quit_==true)
    {
        return false;
    }
    video::Video_subsystem::reload();

    //update
    main_gui_.update();


    //show
    background_.show();
    main_gui_.show();

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
    while(SDL_PollEvent(&event_))
    {
        switch(event_.type)
        {
        case SDL_QUIT:
            return false;
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
        case SDL_KEYDOWN:
            switch(event_.key.keysym.sym)
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
    main_config_(init_config)
{
    quit_ = false;
    //add play button
    gui::Text_button * play_button = new gui::Text_button(init_config,"Play",800,400);
    auto play_func = [this]()
    {
        Game_logic::set_current_mode(new Gaming_mode(main_config_));
    };
    play_button->init_function(play_func);
    play_button->change_size(80);
    play_button->change_position(video::Video_subsystem::get_width()/2-play_button->get_width()/2,400);
    //add options
    gui::Text_button * options_button = new gui::Text_button(init_config,"Options",800,500);
    auto options_func = []()
    {

    };
    options_button->init_function(options_func);
    options_button->change_size(80);
    options_button->change_position(video::Video_subsystem::get_width()/2-options_button->get_width()/2, 550);
    //add exit
    gui::Text_button * exit_button = new gui::Text_button(init_config,"Exit",800,600);
    auto exit_func = [this]()
    {
        quit_ = true;
    };
    exit_button->init_function(exit_func);
    exit_button->change_size(80);
    exit_button->change_position(video::Video_subsystem::get_width()/2-exit_button->get_width()/2,700);
    // initialize background image
    background_.change_image(main_config_->find_string("main_background").c_str());

    main_gui_.add_element(play_button);
    main_gui_.add_element(options_button);
    main_gui_.add_element(exit_button);

}

}//end of main_logic namespace

