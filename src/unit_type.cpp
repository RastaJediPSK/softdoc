#include "unit_type.h"

Tank::Tank()
{
    unit_type = 0;
    unit_terrain = new int [6];
    unit_attack = new int [UNIT_NUMBER];
    unit_terrain[0] = 100;
    unit_terrain[1] = 2;
    unit_terrain[2] = 1;
    unit_terrain[3] = 10;
    unit_terrain[4] = 2;
    unit_terrain[5] = 1;
    unit_attack[0] = 1;
    unit_vision = 5;
    unit_move = 7;
}

Tank::~Tank()
{
    delete [] unit_terrain;
    delete [] unit_attack;
}
    

