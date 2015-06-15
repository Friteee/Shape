#include "map.h"
#include <fstream>
#include <map>
#include <vector>

namespace game
{

void Map::init_map(std::string init_filename)
{
    filename = init_filename;
    std::ifstream in(filename,std::ios_base::in);
    std::map<unsigned int, Tile_type>          buffer_type;
    std::vector<std::pair<unsigned int, Tile>> tiles_buffer;
    Map_Chunk_Id                               chunk;
    unsigned int                               id;
    std::string                                buffer_string;
    while(in>>chunk)
    {
        if(chunk == TILE_TYPE)
        {
            in>>id;
            in>>buffer_string;
            Tile_type buffer;
            buffer.init(buffer_string);
            buffer_type[id] = buffer;
        }
        else if (chunk == TILE)
        {
            in>>id;
            tiles_buffer.push_back(id);
            //TODO
        }
    }
    for(auto & a : tiles_buffer)
    {
        Tile tile_buffer;
        //TODO
    }

}

void Map::init_background(std::string init_filename)
{
    background = new gui::Background(init_filename.c_str());
}

void Map::init_music(std::string init_filename)
{

}

}
