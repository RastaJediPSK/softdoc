/*
 * File:  game.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Game class definition file
 */

#include <ncurses/curses.h>
#include "game.h"
#include "panel.h"
#include "map.h"

Game::Game() : players(), types()
{
	const int num_players = 2;
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
	Map map(100, 100, scr_x-20, scr_y, panel,types);
	//gamemap->map_loop();
    while(true)
    {
        players[0]->reset_units();
        map.map_loop(players[0]);
        clearok(stdscr,true);
        refresh();
        int ch = getch();
        if(ch == 'q')
            break;
        map.redraw(scr_x-20,scr_y);
        players[1]->reset_units();
        map.map_loop(players[1]);
        clearok(stdscr,true);
        refresh();
        ch = getch();
        if(ch == 'q')
            break;
        map.redraw(scr_x-20,scr_y);
    }
}

Game::~Game()
{
    for(int i=0;i<players.size();i++)
        delete players[i];
    for(int i=0;i<types.size();i++)
        delete types[i];
}
