#include "polygon.h"

namespace physics
{

void Polygon::add_point(SDL_Point added)
{
    points.push_back(added);
}

SDL_Point Polygon::get_next_point( unsigned int iterator) const
{
    iterator++;
    if(iterator>=points.size())
        iterator = 0;
    return points[iterator];
}

inline int is_left(SDL_Point p0, SDL_Point p1, SDL_Point p2)
{
     return ( (p1.x - p0.x) * (p2.y - p0.y)
            - (p2.x -  p0.x) * (p1.y - p0.y) );
}


/** \brief Polygon::is_inside returns whether the point is inside the figure, which geometry class represents
 *  It uses winding point algorithm
 * \param SDL_Point point to be searched for
 * \return boolean of collision
 * \author http://geomalgorithms.com/a03-_inclusion.html
 */


bool Polygon::is_inside(SDL_Point searched) const

{
    int winding = 0;    // the  winding number counter

    // loop through all edges of the polygon
    for (unsigned int a = 0 ; a < points.size() ; a++) {   // edge from points[i] to  points[i+1]

        if (points[a].y <= searched.y)
        {                             // start y <= searched.y
            if (get_next_point(a).y  > searched.y)      // an upward crossing
                 if (is_left( points[a], get_next_point(a), searched) > 0)  // searched left of  edge
                     ++winding;            // have  a valid up intersect
        }
        else {                        // start y > searched.y (no test needed)
            if (get_next_point(a).y  <= searched.y)     // a downward crossing
                 if (is_left( points[a], get_next_point(a), searched) < 0)  // searched right of  edge
                     --winding;            // have  a valid down intersect
        }
    }
    return winding;
}


Polygon get_rectangle(int x, int y, int w, int h)
{
    Polygon buffer;
    buffer.add_point(SDL_Point{x   , y  });
    buffer.add_point(SDL_Point{x+w , y  });
    buffer.add_point(SDL_Point{x   , y+h});
    buffer.add_point(SDL_Point{x+w , y+h});
    return buffer;
}

void Polygon::move(int x , int y)
{
    for (auto a : points)
    {
        a.x+=x;
        a.y+=y;
    }
}

const std::vector<SDL_Point>& Polygon::get_points()const
{
    return points;
}

}
