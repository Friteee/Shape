#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <string>
#include <vector>
#include "tile.h"
#include "tile_type.h"
#include "../gui/background.h"
#include "../audio/music.h"

namespace game
{


/** \brief Holder class for tiles and tile types
 *
 * Also holds background and music
 */

enum Map_Chunk_Id
{
    TILE,TILE_TYPE
};

class Map
{
public:
    void                      init_background(std::string init_filename);
    void                      init_music(std::string init_filename);
    void                      init_map(std::string init_filename);
    ~Map();

    inline std::vector <Tile> &      get_tiles()
    {
        return tiles;
    }
    inline std::vector <Tile_type> & get_tile_types()
    {
        return types;
    }
    inline gui::Background &         get_background()
    {
        return *background;
    }
    inline audio::Music &            get_music()
    {
        return music;
    }
private:
    std::vector<Tile>      tiles;
    std::vector<Tile_type> types;
    gui::Background     *  background;
    audio::Music           music;
    std::string            filename;
};

}

#endif // MAP_H_INCLUDED
