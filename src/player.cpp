/*
 * File:  player.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Player class definition file.
 */

#include "player.h"

#include "unit.h"

/* Adds a unit to the players list of current units. */
std::list<Unit *>::iterator Player::add_unit(Unit *unit)
{
	units.push_front(unit);
	return units.begin();
}

/* Removes a unit from the players list of current units. */
void Player::del_unit(std::list<Unit *>::iterator it)
{
	units.erase(it);
}

/*
 * Resets the used flag on all units that player controls.
 * Used at the start of a turn to reset units.
 */
void Player::reset_units()
{
	using std::list;
	for(list<Unit *>::iterator itr = units.begin(); itr != units.end(); ++itr)
		(*itr)->set_used(false);
}

/* Adds the location of a base to the list. */
void Player::add_base(int x, int y)
{
	location_t temp;
	temp.x = x;
	temp.y = y;
	bases.push_back(temp);
}
