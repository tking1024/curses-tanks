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


Vec2D Vec2D::operator+(const Vec2D& other)
{
    double result_x;
    double result_y;
    result_x = x + other.x;
    result_y = y + other.y;
    return Vec2D(result_x,result_y);
}

Vec2D Vec2D::operator*(const double& d_other)
{
    double result_x;
    double result_y;
    result_x = x * d_other;
    result_y = y * d_other;
    return Vec2D(result_x,result_y);
}

Vec2D Vec2D::operator*(const int& i_other)
{
    double result_x;
    double result_y;
    result_x = x * i_other;
    result_y = y * i_other;
    return Vec2D(result_x,result_y);
}

Vec2D Vec2D::operator=(const Vec2D& other)
{
    x = other.x;
    y = other.y;
    return *this;
}
