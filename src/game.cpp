/*
 * File:  game.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class definition file
 */

#include "game.h"

#include <sstream>
#include <string>
#include <curses.h>
#include "panel.h"
#include "map.h"

//Constructs the game object
//created all of the needed objects to start the game
//and contains the main game loop
Game::Game() : players(), types()
{
	const int num_players = 2;
    bool quit = false;
	// Add num_players to the game
	for (int i = 0; i < num_players; ++i)
	{
		Player *p = new Player(i);
		players.push_back(p);
	}

    Tank *t = new Tank();
    types.push_back(t);
    Rock *rock = new Rock();
    types.push_back(rock);
    Paper *paper = new Paper();
    types.push_back(paper);
    Scissors *scissors = new Scissors();
    types.push_back(scissors);
	int scr_x, scr_y;
	getmaxyx(stdscr, scr_y, scr_x);
	//Panel *panel = new Panel(scr_x, scr_y, 20);
	Panel panel(scr_x, scr_y, 20);
	//Map *gamemap = new Map(200, 200, scr_x, scr_y, panel);
	Map map(70, 70, scr_x-20, scr_y, panel,types, players[0], players[1]);
	//gamemap->map_loop();

    while (true)
    {
	    // Player 1's turn
        players[0]->reset_units();
        map.map_loop(players[0]);
        clearok(stdscr,true);
        refresh();

        // End of Player 1's turn.
        // Check if Player 1 won.
        int num_bases = players[1]->get_bases().size();
        int taken_bases = 0;
        for(int i = 0;i<num_bases;i++)
        {
            Location base = players[1]->get_bases()[i];
            Unit *unit_ptr = map.get_tile(base.x,base.y)->unit;
            if(unit_ptr && unit_ptr->get_player() != players[1])
                taken_bases++;
        }
        if(taken_bases == num_bases)
            break;

        // Show player switching window
        quit = end_turn(0);
        if (quit)
                break;

        // Player 2's turn
        map.redraw(scr_x-20, scr_y);
        players[1]->reset_units();
        map.map_loop(players[1]);
        clearok(stdscr,true);
        refresh();

        // End of Player 2's turn.
        // Check if Player 1 won.
        num_bases = players[0]->get_bases().size();
        taken_bases = 0;
        for(int i = 0;i<num_bases;i++)
        {
            Location base = players[0]->get_bases()[i];
            Unit *unit_ptr = map.get_tile(base.x,base.y)->unit;
            if(unit_ptr && unit_ptr->get_player() != players[0])
                taken_bases++;
        }
        if(taken_bases == num_bases)
            break;

        // Switch to player 1
        quit = end_turn(1);
        if (quit)
                break;

        // Redraw screen for Player 1
            map.redraw(scr_x-20, scr_y);
    }
}

//deconstructor for game, deletes players and unit types
Game::~Game()
{
    for(unsigned int i=0;i<players.size();i++)
        delete players[i];
    for(unsigned int i=0;i<types.size();i++)
        delete types[i];
}

// Returns true if 'q' was pressed (quit game)
bool Game::end_turn(bool player)
{
	WINDOW *switch_win = newwin(0, 0, 0, 0);

	// Print "End of "
	std::stringstream ss;
	ss << "End of Player " << player + 1 << "'s turn.";
	std::string s = ss.str();
	wmove(switch_win, LINES/2 - 6, (COLS - s.length()) / 2);
	size_t pos = s.find("Player");
	std::string subs = s.substr(0, pos);
	wprintw(switch_win, subs.c_str());

	// Print "Player n's" in color and bold
	// Player 1: green, 2: red
	wattron(switch_win, COLOR_PAIR(17 + player) | A_BOLD);
	size_t pos2 = s.find("turn") - 1;
	subs = s.substr(pos, pos2 - pos);
	wprintw(switch_win, subs.c_str());

	// Print " turn." normal.
	wattroff(switch_win, COLOR_PAIR(17 + player) | A_BOLD);
	subs = s.substr(pos2);
	wprintw(switch_win, subs.c_str());

	s = "Press q to quit, press any other key to continue...";
	mvwprintw(switch_win, LINES/2 - 3, (COLS - s.length()) / 2, s.c_str());

	// Get a character
	int c = wgetch(switch_win);
	
	// Clear player switching window & close it
	wclear(switch_win);
	wrefresh(switch_win);
	delwin(switch_win);

	// Was 'q' pressed?
	return (c == 'q') ? true : false;
}
