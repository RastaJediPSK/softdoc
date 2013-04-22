/*
 * File:  player.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Player class declaration file
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>
#include "unit.h"

class Player
{
    int id;
	std::list<Unit *> units;

public:
	Player(int i) : id(i), units() { }
    int get_id() { return id; }
    std::list<Unit *>::iterator add_unit(Unit *);
	void del_unit(std::list<Unit *>::iterator);
    void reset_units();
};

#endif
