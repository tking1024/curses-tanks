#if defined(WIN32)
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#endif

#include "Vec2D.hpp"

using namespace std;

Vec2D::Vec2D(double input_x, double input_y)
{
    x = input_x;
    y = input_y;
    
        
}

Vec2D Vec2D::operator=(Vec2D& other)
{
    x = other.x;
    y = other.y;
    
    return Vec2D(other);
}

Vec2D Vec2D::operator+(Vec2D& other)
{
    x = x + other.x;
    y = y + other.y;
    return Vec2D(*this);
}

Vec2D Vec2D::operator*(double& d_other)
{
    x = x * d_other;
    y = y * d_other;
    return Vec2D(*this);
}

Vec2D Vec2D::operator*(int& i_other)
{
    x = x * i_other;
    y = y * i_other;
    return Vec2D(*this);
}
