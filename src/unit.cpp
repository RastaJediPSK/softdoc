/*
 * File:  unit.cpp
 * Authors:  Steve Erikson, Michael, James, Kelly
 * Date:  14 February 2013
 * Description:  Parent unit class implementation file.
 */

#include "unit.h"
#include "player.h"

Unit::Unit(UnitType *unit_type, Player *play) :
    type(unit_type),
    player(play)
{}

int Unit::terrain_cost(int terrain)
{
    return type->get_terrain_cost()[terrain-1];
}
