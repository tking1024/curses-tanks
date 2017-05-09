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
    g.Fill();
	players[0].Draw(g);
	players[1].Draw(g);
	players[0].DrawSettings(turn);
	players[1].DrawSettings(turn);
	refresh();
}

void Die(int player_number)
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(1);
    
    clear();
    refresh();
    
    if (player_number == 1)
    {
    mvaddstr(1, 1, "$$$$$$$\\ $$\\                                                 $$\\         $$$$$$$\\  $$\\                 $$\\" );
    mvaddstr(2, 1, "$$  __$$\\ $$ |                                              $$$$ |        $$  __$$\\ \\__|                $$ |");
    mvaddstr(3, 1, "$$ |  $$ |$$ | $$$$$$\\  $$\\   $$\\  $$$$$$\\   $$$$$$\\        \\_$$ |        $$ |  $$ |$$\\  $$$$$$\\   $$$$$$$ |");
    mvaddstr(4, 1, "$$$$$$$  |$$ | \\____$$\\ $$ |  $$ |$$  __$$\\ $$  __$$\\         $$ |        $$ |  $$ |$$ |$$  __$$\\ $$  __$$ |");
    mvaddstr(5, 1, "$$  ____/ $$ | $$$$$$$ |$$ |  $$ |$$$$$$$$ |$$ |  \\__|        $$ |        $$ |  $$ |$$ |$$$$$$$$ |$$ /  $$ |");
    mvaddstr(6, 1, "$$ |      $$ |$$  __$$ |$$ |  $$ |$$   ____|$$ |              $$ |        $$ |  $$ |$$ |$$   ____|$$ |  $$ |");
    mvaddstr(7, 1, "$$ |      $$ |\\$$$$$$$ |\\$$$$$$$ |\\$$$$$$$\\ $$ |            $$$$$$\\       $$$$$$$  |$$ |\\$$$$$$$\\ \\$$$$$$$ |");
    mvaddstr(8, 1, "\\__|      \\__| \\_______| \\____$$ | \\_______|\\__|            \\______|      \\_______/ \\__| \\_______| \\_______|");
    mvaddstr(9, 1, "                        $$\\   $$ |                                                                          ");
    mvaddstr(10, 1, "                        \\$$$$$$  |                                                                          ");
    mvaddstr(11, 1, "                         \\______/                                                                           ");
        refresh();
        MySleep(100000);
        endwin();
     
    }
    if (player_number == 2)
    {
        
        mvaddstr(1, 1, " /$$$$$$$  /$$        /$$$$$$  /$$     /$$ /$$$$$$$$ /$$$$$$$         /$$$$$$        /$$$$$$$  /$$$$$$ /$$$$$$$$ /$$$$$$$ ");
        mvaddstr(2, 1, "| $$__  $$| $$       /$$__  $$|  $$   /$$/| $$_____/| $$__  $$       /$$__  $$      | $$__  $$|_  $$_/| $$_____/| $$__  $$");
        mvaddstr(3, 1, "| $$  \\ $$| $$      | $$  \\ $$ \\  $$ /$$/ | $$      | $$  \\ $$      |__/  \\ $$      | $$  \\ $$  | $$  | $$      | $$  \\ $$");
        mvaddstr(4, 1, "| $$$$$$$/| $$      | $$$$$$$$  \\  $$$$/  | $$$$$   | $$$$$$$/        /$$$$$$/      | $$  | $$  | $$  | $$$$$   | $$  | $$");
        mvaddstr(5, 1, "| $$____/ | $$      | $$__  $$   \\  $$/   | $$__/   | $$__  $$       /$$____/       | $$  | $$  | $$  | $$__/   | $$  | $$");
        mvaddstr(6, 1, "| $$      | $$      | $$  | $$    | $$    | $$      | $$  \\ $$      | $$            | $$  | $$  | $$  | $$      | $$  | $$");
        mvaddstr(7, 1, "| $$      | $$$$$$$$| $$  | $$    | $$    | $$$$$$$$| $$  | $$      | $$$$$$$$      | $$$$$$$/ /$$$$$$| $$$$$$$$| $$$$$$$/");
        mvaddstr(8, 1, "|__/      |________/|__/  |__/    |__/    |________/|__/  |__/      |________/      |_______/ |______/|________/|_______/ ");
        refresh();
        MySleep(100000);
        endwin();
    }
}
    


void Shoot(Ground & g, Player * players, int turn)
{
	double angle = players[turn].angle / 180.0 * PI;

    Vec2D p0 (players[turn].col, LINES - g.ground.at(players[turn].col));
    Vec2D force(sin(angle) * players[turn].power * 0.2, cos(angle) * players[turn].power * 0.2);
 	Vec2D gravity(0, -9.8);
	
	double time_divisor = 15.0;
   
    if (players[turn].s == RIGHT)
		force.x = -force.x;
		 
	double x = 0.0;
	double y = 0.0;
    
   	for (int i = 1; i < 10000; i++)
	{
		double di = i / time_divisor;
        Vec2D pN(x,y);

		pN.x = (int)(p0.x + di * force.x);
		pN.y = p0.y + di * force.y + (di * di + di) * gravity.y / time_divisor;
		pN.y = (int)(LINES - pN.y);
        
		if (pN.x < 1 || pN.x >= COLS - 2)
			break;
        if (pN.y < 1)
        {
            
            MySleep(50);
            continue;
        }
        
        if (pN.y > g.ground.at((int)pN.x))
            break;
        
        move((int)pN.y - 1, (int)pN.x + 1);
        addch('*');
        refresh();
        MySleep(50);
        
        if (players[turn].Hit((int)pN.x, (int)pN.y, g, players[abs(turn - 1)]))
        {
            players[abs(turn - 1)].life_counter--;
            break;
        }
        
        if (players[turn].life_counter == 0)
        {
            Die(turn + 1);
        }
        refresh();
        MySleep(50);
        
   	}
    
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
    
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    
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
        
        case 'k':
            Die(1);
            break;
                
        case 'j':
            Die(2);
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

