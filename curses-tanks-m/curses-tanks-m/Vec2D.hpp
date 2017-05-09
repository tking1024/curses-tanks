#pragma once
#include "ground.hpp"
#include "player.hpp"

class Vec2D
{
public:
    double x;
    double y;
    
    Vec2D(double input_x, double input_y);
    
    Vec2D operator+(const Vec2D& other);
    Vec2D operator*(const double& d_other);
    Vec2D operator*(const int& i_other);
    Vec2D operator=(const Vec2D& other);

    
    
};
