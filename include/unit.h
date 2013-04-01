/*
 * File:  unit.h
 * Authors:  Steve Erikson, Michael, Kelly, James
 * Date:  14 February 2013
 * Description:  Parent Unit class declaration file.
 */

#ifndef UNIT_H_
#define UNIT_H_

#include <ncurses/curses.h>
#include "unit_type.h"
#include "player.h"

class Unit
{
    UnitType *type;
    Player *p;

    public:
    Unit(UnitType *unit_type, Player *player);
    int terrain_cost(int terrain);
    int symbol() { return type->get_unit_symbol(); }
    //other gameplay functions
};



#endif
