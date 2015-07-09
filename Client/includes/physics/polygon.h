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
    void                          add_point (SDL_Point added);
    bool                          is_inside (SDL_Point searched) const;
    void                          set       (int init_x, int init_y);
    void                          get       (int * get_x , int * get_y);
    const std::vector<SDL_Point>& get_points() const;
private:
    int x,y;
    SDL_Point    get_next_point(unsigned int iterator) const;
    std::vector<SDL_Point> points;
    std::vector<SDL_Point> starting_points;

};

Polygon get_rectangle(int x, int y, int w, int h);

}

#endif // GEOMETRY_H_INCLUDED
