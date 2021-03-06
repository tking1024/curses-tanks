#pragma once
#include "ground.hpp"

enum Side
{
	LEFT,
	RIGHT
};

class Player
{
public:
	Player();
	void Draw(Ground & ground);
	void Initialize(int column, int line, Side side);
	void DrawSettings(int turn);
	void PowerUp();
	void PowerDown();
	void AngleUp();
	void AngleDown();
    
    bool Hit(int column, int line, Ground & g, Player & p);

	int col;
	double power;
	double angle;
	Side s;
    int life_counter = 3;

	static const int power_increment;
	static const double angle_increment;
};
