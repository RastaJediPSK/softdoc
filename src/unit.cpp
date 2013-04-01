/*
 * File:  unit.cpp
 * Authors:  Steve Erikson, Michael, James, Kelly
 * Date:  14 February 2013
 * Description:  Parent unit class implementation file.
 */

#include "unit.h"

void Unit::attack(Unit &enemy)
{
	int dmg_taken = 0;
	int dmg_dealt = 0;
	// dmg = something based on off and def of both units
	health -= dmg_taken;
	enemy.health -= dmg_dealt;
}
