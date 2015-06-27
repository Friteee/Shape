#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include <SDL.h>
#include <vector>

namespace physics
{

/** \class Polygon
 * \brief Polygon of a figure, consisting of points
 *
 *
 */


class Polygon
{
public:
    void                          add_point(SDL_Point added);
    bool                          is_inside(SDL_Point searched) const;
    void                          move     (int x, int y);
    const std::vector<SDL_Point>& get_points() const;
private:
    SDL_Point    get_next_point(unsigned int iterator) const;
    std::vector<SDL_Point> points;

};

Polygon get_rectangle(int x, int y, int w, int h);

}

#endif // GEOMETRY_H_INCLUDED
