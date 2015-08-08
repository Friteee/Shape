#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <string>
#include <vector>
#include "static_object.h"
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
    TILE,TILE_TYPE,BACKGROUND
};

class Map
{
public:
    void                      init_background(std::string init_filename);
    void                      init_music(std::string init_filename);
    void                      init_map(std::string init_filename);
    ~Map();

    inline std::vector <Static_object> &      get_tiles()
    {
        return tiles_;
    }
    inline std::vector <Object_type> & get_tile_types()
    {
        return types_;
    }
    inline gui::Background &         get_background()
    {
        return *background_;
    }
    inline audio::Music &            get_music()
    {
        return music_;
    }
private:
    std::vector<Static_object> tiles_;
    std::vector<Object_type>   types_;
    gui::Background          * background_;
    audio::Music               music_;
    std::string                filename_;
};

}

#endif // MAP_H_INCLUDED
