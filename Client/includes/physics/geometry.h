#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <SDL.h>
#include <vector>

namespace physics
{

/** \class Geometry
 * \brief Geometry of a figure, consisting of points
 *
 *
 */


class Geometry
{
public:
    void                    add_point(SDL_Point added);
    bool                    is_inside(SDL_Point searched);
    void                    move     (int x, int y);
    std::vector<SDL_Point>& get_points();
private:
    SDL_Point    get_next_point(unsigned int iterator);
    std::vector<SDL_Point> points;

};

Geometry get_rectangle(int x, int y, int w, int h);

}

#endif // GEOMETRY_H_INCLUDED
