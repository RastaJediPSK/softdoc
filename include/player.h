/*
 * File:  player.h
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Player class declaration file.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <vector>

class Unit;

/* Struct to hold locations. */
struct location_t
{
	int x;
	int y;
};

/* Player class, holds data for each player. */
class Player
{
	int id;
	std::list<Unit *> units;
	std::vector<location_t> bases;

public:
	Player(int i) : id(i), units(), bases() { }
	int get_id() const { return id; }
	std::vector<location_t> const &get_bases() const { return bases; }
	std::list<Unit *>::iterator add_unit(Unit *);
	void del_unit(std::list<Unit *>::iterator);
	void reset_units();
	void add_base(int x, int y);
};

#endif	/* PLAYER_H */
