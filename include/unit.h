/*
 * File:  unit.h
 * Authors:  Steve Erikson, Michael, Kelly, James
 * Date:  14 February 2013
 * Description:  Parent Unit class declaration file.
 */

#ifndef UNIT_H_
#define UNIT_H_

#include <string>
#include <list>
#include <ncurses/curses.h>
#include <cstdlib>
#include "unit_type.h"

class Player; //prototype to avoid dependency

class Unit
{
    UnitType *type;
    Player *player;
    bool used;
    std::list<Unit *>::iterator place;
    int mapx,mapy;

    public:
    Unit(UnitType *unit_type, Player *play, int x, int y);
    ~Unit();
    int terrain_cost(int terrain);
    int attack(int label);
    int get_label() { return type->get_unit_label(); }
    int symbol() { return type->get_unit_symbol(); }
    std::string get_name() { return type->get_unit_name(); }
    bool get_used() { return used; }
    void set_used(bool b) { used = b; }
    int get_move() { return type->get_unit_move(); }
    void move(int x, int y);
    int get_x() { return mapx; }
    int get_y() { return mapy; }
    Player *get_player() { return player; }
    //other gameplay functions
};



#endif
