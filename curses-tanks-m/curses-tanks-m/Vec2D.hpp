#pragma once
#include "ground.hpp"
#include "player.hpp"

class Vec2D
{
public:
    double x;
    double y;
    
    Vec2D(double input_x, double input_y);
    
    Vec2D operator+(Vec2D& other);
    Vec2D operator*(double& d_other);
    Vec2D operator*(int& i_other);
    Vec2D operator=(Vec2D& other);

    
    
};
