#include "polygon.h"

namespace physics
{

void Polygon::add_point(SDL_Point added)
{
    starting_points_.push_back(added);
    points_.push_back(added);
}

SDL_Point Polygon::get_next_point( unsigned int iterator) const
{
    iterator++;
    if(iterator>=points_.size())
        iterator = 0;
    return points_[iterator];
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
    for (unsigned int a = 0 ; a < points_.size() ; a++) {   // edge from points_[i] to  points_[i+1]

        if (points_[a].y <= searched.y)
        {                             // start y <= searched.y
            if (get_next_point(a).y  > searched.y)      // an upward crossing
                 if (is_left( points_[a], get_next_point(a), searched) > 0)  // searched left of  edge
                     ++winding;            // have  a valid up intersect
        }
        else {                        // start y > searched.y (no test needed)
            if (get_next_point(a).y  <= searched.y)     // a downward crossing
                 if (is_left( points_[a], get_next_point(a), searched) < 0)  // searched right of  edge
                     --winding;            // have  a valid down intersect
        }
    }
    return winding;
}


Polygon get_rectangle(int x, int y, int w, int h)
{
    Polygon buffer;
    buffer.add_point(SDL_Point{0   , 0  });
    buffer.add_point(SDL_Point{w   , 0  });
    buffer.add_point(SDL_Point{0   , h  });
    buffer.add_point(SDL_Point{w   , h  });
    buffer.set(x , y);
    return buffer;
}

void Polygon::set(int init_x , int init_y)
{
    x_=init_x;
    y_=init_y;
    for(unsigned int a = 0; a < points_.size() ; a++)
    {
        points_[a].x = starting_points_[a].x + x_;
        points_[a].y = starting_points_[a].y + y_;
    }
}

void Polygon::get(int * get_x , int * get_y)
{
    *get_x = x_;
    *get_y = y_;
}

const std::vector<SDL_Point>& Polygon::get_points()const
{
    return points_;
}

}
