/*
 * File:  player.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Player class implementation file
 */

#include "player.h"

std::list<Unit *>::iterator Player::add_unit(Unit *unit)
{
	this->units.push_front(unit);
    return this->units.begin();
}

void Player::del_unit(std::list<Unit *>::iterator it)
{
	this->units.erase(it);
}

void Player::reset_units()
{
    for(std::list<Unit *>::iterator itr=units.begin();itr!=units.end();itr++)
        (*itr)->set_used(false);
}
