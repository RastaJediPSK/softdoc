/*
 * File:  unit.cpp
 * Authors:  Steve Erikson, Michael, James, Kelly
 * Date:  14 February 2013
 * Description:  Parent unit class implementation file.
 */

#include "unit.h"
#include "player.h"

Unit::Unit(UnitType *unit_type, Player *play, int x, int y) :
    type(unit_type),
    player(play),
    used(false),
    place(),
    mapx(x),
    mapy(y)
{
    if(play != NULL)
        place = play->add_unit(this);
}

Unit::~Unit()
{
    player->del_unit(place);
}

int Unit::terrain_cost(int terrain)
{
    return type->get_terrain_cost()[terrain-1];
}

int Unit::attack(int label)
{
    int num = std::rand() % 10 + 1;
    int *ptr = type->get_unit_attack();
    if(num <= ptr[label*2])
        return 0;
    if(num <= ptr[label*2+1])
        return 1;
    return 2;
}

void Unit::move(int x, int y)
{
    mapx = x;
    mapy = y;
}
