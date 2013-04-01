/*
 * File:  player.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Player class implementation file
 */

#include "player.h"

void Player::add_unit(Unit *unit)
{
	this->units.push_back(unit);
}

void Player::del_unit(std::vector<Unit *>::iterator it)
{
	this->units.erase(it);
}
