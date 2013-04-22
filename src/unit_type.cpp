#include "unit_type.h"

Tank::Tank()
{
    name = "Tank";
    unit_label = 0;
    terrain_cost = new int [6];
    unit_attack = new int [UNIT_NUMBER*2];
    terrain_cost[0] = 100;
    terrain_cost[1] = 2;
    terrain_cost[2] = 1;
    terrain_cost[3] = 10;
    terrain_cost[4] = 2;
    terrain_cost[5] = 1;
    unit_attack[0] = 4;
    unit_attack[1] = 6;
    unit_vision = 5;
    unit_move = 20;
    unit_symbol = 'T';
}

Tank::~Tank()
{
    delete [] terrain_cost;
    delete [] unit_attack;
}
    

