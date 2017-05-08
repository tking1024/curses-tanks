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
    
    Vec2D operator+(const Vec2D& other);
    Vec2D operator*(const double& other);
    
    
}
