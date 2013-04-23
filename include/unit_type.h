#ifndef UNIT_TYPE_H
#define UNIT_TYPE_H

#define UNIT_NUMBER 4

#include <string>

//Parent class to unit type classes that act as
//a flyweight to store data about different unit types
class UnitType
{
protected:
    int *terrain_cost;
    int *unit_attack;
    int unit_label;
    int unit_vision;
    int unit_move;
    int unit_symbol;
    std::string name;
    int unit_cost;
    
    //unused constructors to stop warnings
    UnitType(const UnitType &u);
    void operator=(const UnitType &u);

public:
    UnitType() : terrain_cost(NULL), unit_attack(NULL), unit_label(-1), unit_vision(0), unit_move(0), unit_symbol(0), name(""), unit_cost(0) {}
    virtual ~UnitType() { }
    int *get_terrain_cost() { return terrain_cost; }
    int *get_unit_attack() { return unit_attack; }
    int get_unit_label() { return unit_label; }
    int get_unit_vision() { return unit_vision; }
    int get_unit_move() { return unit_move; }
    int get_unit_symbol() { return unit_symbol; }
    std::string get_unit_name() { return name; } 
    int get_unit_cost() { return unit_cost; }
};

//Tank unit data class
class Tank : public UnitType
{
    public:
    Tank();
    ~Tank();
};

//Rock unit data class
class Rock : public UnitType
{
    public:
    Rock();
    ~Rock();
};

//Paper unit data class
class Paper : public UnitType
{
    public:
    Paper();
    ~Paper();
};

//Scissors unit data class
class Scissors :public UnitType
{
    public:
    Scissors();
    ~Scissors();
};
#endif
