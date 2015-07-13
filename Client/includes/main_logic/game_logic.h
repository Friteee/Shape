#ifndef GAME_LOGIC_H_INCLUDED
#define GAME_LOGIC_H_INCLUDED

#include "../video/video_subsystem.h"
#include "../gui/background.h"
#include "../video/camera.h"
#include "../utility/configuration.h"
#include "../audio/audio.h"
#include "../physics/physics_engine.h"
#include "gaming_mode.h"
#include "main_menu_mode.h"

namespace main_logic
{


/**
 * \brief Game_logic class
 * First thing to be created
 * Handles physics, used to initialize the game,
 * audio, video and other subsystems
 */

class Game_logic
{

public:

    // initialization of game_logic
    static bool                      initialize(const char *);
    // clean up after game_logic
    static void                      free();
    // main loop
    static void                      run();
    // getter of instance of game_logic
    static Game_logic&               get_instance();
    // set the current mode
    static void                      set_current_mode(Program_mode * init_mode);
    // get physics engine
    static physics::Physics_engine & get_engine();
    // config getter
    static utility::Configuration &  get_config();
    // destructor
    ~Game_logic();

private:
    // configuration
    utility::Configuration main_config_;
    //width and height
    int                    width_,
                           height_;
    //is it full-screen?
    bool                   fullscreen_;
    // constructor
    Game_logic();
    // remove all other means to create video_subsystem
    Game_logic( Game_logic const& x)= delete;
    // instance for maintaining singleton
    static Game_logic* instance_;
    // bool to know if the instance was created without errors
    bool           is_created_;
    // event handler
    SDL_Event      event_;
    // current mode
    Program_mode * current_;
    // program mode marked for deletion
    Program_mode * previous_;
    // physics engine
    physics::Physics_engine engine_;

};





}// game logic namespace

#endif // GAME_LOGIC_H_INCLUDED
