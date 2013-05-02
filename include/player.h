/*
 * File:  player.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Player class declaration file
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>
#include <vector>
#include "unit.h"

//Struct to hold locations
struct Location
{
    int x;
    int y;
};

//Player class, holds data for each player
class Player
{
    int id;
	std::list<Unit *> units;
    std::vector<Location> bases;

public:
	Player(int i) : id(i), units(), bases() { }
    int get_id() { return id; }
    std::list<Unit *>::iterator add_unit(Unit *);
	void del_unit(std::list<Unit *>::iterator);
    void reset_units();
    void add_base(int x, int y);
    std::vector<Location> &get_bases() { return bases; }
};

#endif
