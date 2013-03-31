/*
 * File:  player.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>
#include "unit.h"

class Player
{
    int resources;
    std::list<Unit *> units;

public:
	Player();	// ctor
    void add_unit(Unit *unit);
};

#endif
