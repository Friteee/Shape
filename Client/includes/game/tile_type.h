#ifndef TILE_TYPE_H_INCLUDED
#define TILE_TYPE_H_INCLUDED

#include <string>
#include <SDL.h>
#include "../video/texture.h"

namespace game
{

class Tile_type
{
public:
    Tile_type();
    bool get_invincibility();
    void set_invincibility( bool set_invincible );
    void init_texture     ( std::string filename);
    void blit             ( SDL_Point location  );
private:
    video::Texture texture;
    bool           invincible;
};

}

#endif // TILE_TYPE_H_INCLUDED
