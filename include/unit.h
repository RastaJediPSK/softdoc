/*
 * File:  unit.h
 * Authors:  Steve Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  14 February 2013
 * Description:  Parent Unit class declaration file.
 */

#ifndef UNIT_H
#define UNIT_H

#include <list>
#include <string>
#include "unit_type.h"

class Player;

/* Class for each individual unit object. */
class Unit
{
	UnitType *type;
	Player *player;
	bool used;
	std::list<Unit *>::iterator place;
	int mapx, mapy;

	// Unused constructors to stop warnings
	Unit(const Unit &u);
	void operator=(const Unit &u);

public:
	Unit(UnitType *unit_type, Player *play, int x, int y);
	~Unit();
	int terrain_cost(int terrain) const;
	int attack(int label);
	int get_label() const { return type->get_unit_label(); }
	int symbol() const { return type->get_unit_symbol(); }
	std::string get_name() const { return type->get_unit_name(); }
	bool get_used() const { return used; }
	void set_used(bool b) { used = b; }
	int get_move() const { return type->get_unit_move(); }
	void move(int x, int y);
	int get_x() const { return mapx; }
	int get_y() const { return mapy; }
	Player *get_player() const { return player; }
};

#endif	/* UNIT_H */
