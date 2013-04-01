/*
 * File:  unit.h
 * Authors:  Steve Erikson, Michael, Kelly, James
 * Date:  14 February 2013
 * Description:  Parent Unit class declaration file.
 */

#ifndef UNIT_H_
#define UNIT_H_

class Unit
{
protected:
	int health;
	int off;
	int def;

public:
	Unit(int off, int def) : health(100), off(off), def(def) { }
	virtual ~Unit();
	void attack(Unit &);	/* attack other units */
};

class Infantry : Unit
{
public:
	Infantry() : Unit(1, 1) { }
};

class Tank : Unit
{
public:
	Tank() : Unit(2, 2) { }
};

#endif
