/*
 * File:  player.h
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "unit.h"

class Player
{
	int cash;
	std::vector<Unit *> units;

public:
	Player() : cash(0) { }
	inline int get_cash() const { return cash; }
	void set_cash(int);
	int add_cash(int);
	int sub_cash(int);
	void add_unit(Unit *);
	void del_unit(std::vector<Unit *>::iterator);
};

#endif
