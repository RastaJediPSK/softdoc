/*
 * File:  unit_type.cpp
 * Authors:  Stephen Erikson, Michael Pomeranz, Kelly DeBarr
 * Date:  1 April 2013
 * Description:  UnitType parent and derived classes definition file.
 */

#include "unit_type.h"

/* Tank constructor, sets all data for the class. */
Tank::Tank()
{
	name = "Tank";
	unit_label = 0;
	terrain_cost = new int[6];
	unit_attack = new int[UNIT_NUMBER * 2];
	terrain_cost[0] = 100;
	terrain_cost[1] = 2;
	terrain_cost[2] = 1;
	terrain_cost[3] = 10;
	terrain_cost[4] = 2;
	terrain_cost[5] = 1;
	unit_attack[0] = 5;
	unit_attack[1] = 7;
	unit_attack[2] = 5;
	unit_attack[3] = 7;
	unit_attack[4] = 5;
	unit_attack[5] = 7;
	unit_attack[6] = 5;
	unit_attack[7] = 7;
	unit_vision = 5;
	unit_move = 20;
	unit_symbol = 'T';
}

/* Tank deconstuctor. */
Tank::~Tank()
{
	delete[] terrain_cost;
	delete[] unit_attack;
}
    
/* Rock constructor, creates data for rock unit. */
Rock::Rock()
{
	name = "Rock";
	unit_label = 1;
	terrain_cost = new int[6];
	unit_attack = new int[UNIT_NUMBER * 2];
	terrain_cost[0] = 100;
	terrain_cost[1] = 2;
	terrain_cost[2] = 1;
	terrain_cost[3] = 10;
	terrain_cost[4] = 2;
	terrain_cost[5] = 1;
	unit_attack[0] = 5;
	unit_attack[1] = 7;
	unit_attack[2] = 5;
	unit_attack[3] = 7;
	unit_attack[4] = 2;
	unit_attack[5] = 4;
	unit_attack[6] = 8;
	unit_attack[7] = 9;
	unit_vision = 5;
	unit_move = 20;
	unit_symbol = 'R';
}
	
/* Rock deconstructor. */
Rock::~Rock()
{
	delete[] terrain_cost;
	delete[] unit_attack;
}

/* Paper constructor, sets data for paper unit. */
Paper::Paper()
{
	name = "Paper";
	unit_label = 2;
	terrain_cost = new int[6];
	unit_attack = new int[UNIT_NUMBER * 2];
	terrain_cost[0] = 100;
	terrain_cost[1] = 2;
	terrain_cost[2] = 1;
	terrain_cost[3] = 10;
	terrain_cost[4] = 2;
	terrain_cost[5] = 1;
	unit_attack[0] = 5;
	unit_attack[1] = 7;
	unit_attack[2] = 8;
	unit_attack[3] = 9;
	unit_attack[4] = 5;
	unit_attack[5] = 7;
	unit_attack[6] = 2;
	unit_attack[7] = 4;
	unit_vision = 5;
	unit_move = 20;
	unit_symbol = 'P';
}

/* Paper deconstuctor. */
Paper::~Paper()
{
	delete[] terrain_cost;
	delete[] unit_attack;
}

/* Scissors constructor, creates data for the scissors unit. */
Scissors::Scissors()
{
	name = "Scissors";
	unit_label = 3;
	terrain_cost = new int[6];
	unit_attack = new int[UNIT_NUMBER * 2];
	terrain_cost[0] = 100;
	terrain_cost[1] = 2;
	terrain_cost[2] = 1;
	terrain_cost[3] = 10;
	terrain_cost[4] = 2;
	terrain_cost[5] = 1;
	unit_attack[0] = 5;
	unit_attack[1] = 7;
	unit_attack[2] = 2;
	unit_attack[3] = 4;
	unit_attack[4] = 8;
	unit_attack[5] = 9;
	unit_attack[6] = 5;
	unit_attack[7] = 7;
	unit_vision = 5;
	unit_move = 20;
	unit_symbol = 'S';
}

/* Scissors deconstructor. */
Scissors::~Scissors()
{
	delete[] terrain_cost;
	delete[] unit_attack;
}
