#ifndef TILE_TYPE_H_INCLUDED
#define TILE_TYPE_H_INCLUDED

#include <string>
#include <SDL.h>
#include "../video/texture.h"

namespace game
{

/** \brief Basic information a bout tile
 *
 *  Kinda similar to flyweight pattern
 */


class Tile_type
{
public:
    Tile_type();
    bool get_invincibility();
    void set_invincibility( bool set_invincible );
    void init_texture     ( std::string filename);
    void blit             ( SDL_Point location  );
    void set_id           ( unsigned int init_id);
    unsigned int get_id ()
    {
        return id_;
    }
private:
    video::Texture texture_;
    bool           invincible_;
    unsigned int   id_;
};

}

#endif // TILE_TYPE_H_INCLUDED
