#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

#if defined(WIN32)
#include <Windows.h>
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#include <unistd.h>
#endif

#include "ground.hpp"
#include "player.hpp"
#include "Vec2D.hpp"

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const double PI = 3.141592653589793238463;

void MySleep(int milliseconds)
{
#if defined(WIN32)
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}
void DrawScreen(Ground & g, Player * players, int turn)
{
	erase();
	box(stdscr, 0, 0);
	g.Draw();
	players[0].Draw(g);
	players[1].Draw(g);
	players[0].DrawSettings(turn);
	players[1].DrawSettings(turn);
	refresh();
}

//http://www.iforce2d.net/b2dtut/projected-trajectory

void Shoot(Ground & g, Player * players, int turn)
{
	double angle = players[turn].angle / 180.0 * PI;

	
	//double y_component = sin(angle) * players[turn].power * 0.2;
	//double x_component = cos(angle) * players[turn].power * 0.2;
	
	Vec2D p0(players[turn].col, g.ground.at(players[turn].col));
 	Vec2D force(sin(angle) * players[turn].power * 0.2, cos(angle) * players[turn].power * 0.2);
 	Vec2D gravity(0, -0.98); // or a different value of your choosing.
	
	//double pNx;
	//double pNy;
	//double time_divisor = 15.0;

    //double time_divisor = 15.0;
    //double y_component = sin(angle) * players[turn].power * 0.2;
	//double x_component = cos(angle) * players[turn].power * 0.2;

	
    //Vec2D p0 (players[turn].col, LINES - g.ground.at(players[turn].col));
    //Vec2D force (cos(angle) * players[turn].power * 0.2,sin(angle) * players[turn].power * 0.2);
    //Vec2D gravity (0, -9.8);
    
	//double pNx;
	//double pNy;
		
	if (players[turn].s == RIGHT)
		force.x = -force.x;

	//double p0x = players[turn].col;
	//double p0y = g.ground.at(players[turn].col);
	// higher ground numbers are lower altitudes (0 is first line, etc).

	p0.y = LINES - p0.y;
		 
	//double x = 0.0;
	//double y = 0.0;
    
   	/*for (int i = 1; i < 10000; i++)
	{
		double di = i / time_divisor;
		
		Vec2D pN(x , y);

		pN.x = (int)(p0.x + di * force.x);
		pN.y = p0.y + di * force.y + (di * di + di) * -9.8 / time_divisor / 1.5;
		pN.y = (int)(LINES - pN.y);
        
		if (pN.x < 1 || pN.x >= COLS - 2)
			break;
		if (pN.y < 1) {
   	for (int i = 1; i < 10000; i++)
	{
		double di = i / time_divisor;
        Vec2D pN = p0 + (force * di) + gravity * (di * di + di) * 0.5;
        
        //pNx = (int)(p0x + di * x_component);
		//pNy = p0y + di * y_component + (di * di + di) * -9.8 / time_divisor / 1.5;
		//pNy = (int)(LINES - pNy);
        
		if (pN.x < 1 || pN.x >= COLS - 2)
			break;
		if (pN.y < 1)
        {

			MySleep(50);
			continue;
		}
		//if (pNy >= LINES - 2)
			//break;
		if (pN.y > g.ground.at((int)pN.x))
			break;
        
        if (players[turn].Hit((int)pN.x, (int)pN.y, players[abs(turn-1)]))
            {
                players[abs(turn - 1)].life_counter--;
                break;
            }
        

        move((int)pN.y - 1, (int)pN.x + 1);

        move((int)pN.x - 1, (int)pN.y + 1);

		addch('*');
        refresh();
		MySleep(50);
    
        
        //if (players[abs(turn-1)].Hit((int)pNx, (int)pNy players[abs(turn - 1)]))
        //{
        //    players[abs(turn - 1)].life_counter--;
        //    break;
        //}
    }*/

}

int main(int argc, char * argv[])
{
	srand((unsigned int)time(nullptr));

	int turn = 0;
	bool keep_going = true;
	Ground g;
	Player players[2];

	initscr();
	noecho();
	keypad(stdscr, 1);

	g.InitializeGround();
	players[0].Initialize(rand() % (COLS / 4), g.ground.at(players[0].col) - 1, LEFT);
	players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, g.ground.at(players[1].col) - 1, RIGHT);

	DrawScreen(g, players, turn);
	while (keep_going)
	{
		bool show_char = false;
		int c = getch();
		switch (c)
		{
		case 27:
			keep_going = false;
			break;

		case '<':
			players[turn].PowerDown();
			break;

		case '>':
			players[turn].PowerUp();
			break;

		case 'u':
			players[turn].AngleUp();
			break;

		case 'd':
			players[turn].AngleDown();
			break;

		case 10:
		case KEY_ENTER:
#if defined(WIN32)
		case PADENTER:
#endif
			Shoot(g, players, turn);
			turn = 1 - turn;
			break;

		default:
			show_char = true;
			break;
		}
        DrawScreen(g, players, turn);
		if (show_char) {
			move(0, 1);
			stringstream ss;
			ss << setw(4) << c << " ";
			addstr(ss.str().c_str());
			refresh();
		}
	}
	erase();
	addstr("Hit any key to exit");
	refresh();
	getch();
	echo();
	endwin();
	return 0;
}

