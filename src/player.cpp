/*
 * File:  player.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, James Lenze, Kelly DeBarr
 * Date:  28 March 2013
 * Description:  Player class implementation file
 */

#include "player.h"

Player::Player() : cash(0)
{

}

void Player::set_cash(int amount)
{
	this->cash = amount;
}

int Player::add_cash(int amount)
{
	this->cash += amount;
	return this->cash;
}

int Player::sub_cash(int amount)
{
	this->cash -= amount;
	return this->cash;
}

void Player::add_unit(Unit *unit)
{
	this->units.push_back(unit);
}

void Player::del_unit(std::vector<Unit *>::iterator it)
{
	this->units.erase(it);
}
