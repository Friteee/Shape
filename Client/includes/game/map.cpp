#include "map.h"
#include <fstream>
#include <map>
#include <vector>

namespace game
{

void Map::init_map(std::string init_filename)
{
    struct Tile_info
    {
        unsigned int id,
                     width,
                     height;
        int          x,
                     y;
    };

    struct Tile_type_info
    {
        unsigned int id;
        std::string  filename;
        bool         invincibility;
    };

    filename_ = init_filename;
    std::ifstream in(filename_ , std::ios_base::in);
    std::vector<Tile_type_info>                buffer_type;   // buffer for information about types of tiles
    std::vector<Tile_info>                     tiles_buffer;  // buffer for information about tiles
    Map_Chunk_Id                               chunk;         // type of the info chunk
    unsigned int                               type_id;       // id of the tile_type and buffer for map chunk id
    std::string                                buffer_string; // string as a buffer for filename
    while(in >> type_id)
    {
        chunk = static_cast <Map_Chunk_Id> (type_id);
        if(chunk == TILE_TYPE)
        {

            Tile_type_info buffer;
            in>>buffer.id;
            in>>buffer.filename;
            in>>buffer.invincibility;
            buffer_type.push_back(buffer);
        }
        else if (chunk == TILE)
        {
            Tile_info info;
            in>>info.id;
             in>>info.x>>info.y>>info.width>>info.height;
            tiles_buffer.push_back(info);
            //TODO
        }
    }

    for(auto & a : buffer_type)
    {
        Tile_type buffer;
        buffer.set_id           (a.id);
        buffer.init_texture     (a.filename);
        buffer.set_invincibility(a.invincibility);
        types_.push_back(buffer);
    }
    for(auto & a : tiles_buffer)
    {
        Tile buffer;
        buffer.init_geometry(physics::get_rectangle(a.x, a.y, a.width, a.height));
        for (auto & b : types_)
        {
            if(a.id == b.get_id())
            {
                buffer.init_tile_type(&b);
            }
        }
    }

}

void Map::init_background(std::string init_filename)
{
    background_ = new gui::Background(init_filename.c_str());
}

void Map::init_music(std::string init_filename)
{
    music_.init(init_filename);
}

}
