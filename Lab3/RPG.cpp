#include "RPG.h"
#include <cstdlib>

RPG::RPG()
{
    name = "NPC";
    health = 100;
    strength = 10;
    defense = 10;
    type = "warrior";
    skills[0] = "slash";
    skills[1] = "parry";
}

RPG::RPG(string n, int h, int s, int d, string t)
{
    this->name = n;
    this->health = h;
    this->strength = s;
    this->defense = d;
    this->type = t;

    this->setSkills();
}

void RPG::setSkills()
{
    if (type == "mage")
    {
        skills[0] = "fire";
        skills[1] = "thunder";
    } 
    else if (type == "thief")
    {
        skills[0] = "pilfer";
        skills[1] = "jab";
    } 
    else if (type == "archer")
    {
        skills[0] = "parry";
        skills[1] = "crossbow_attack";
    } 
    else
    {
        skills[0] = "slash";
        skills[1] = "parry";
    }
}

void RPG::printAction(string skill, RPG opponent)
{
    printf("%s used %s on %s\n", name.c_str(), skill.c_str(), opponent.getName().c_str());
}

void RPG::updateHealth(int newHealth)
{
    this->health = newHealth;
}

//void RPG::attack(RPG *){}

//void RPG::useSkill(RPG *){}

bool RPG::isAlive() const
{
    return health > 0;
}

string RPG::getName() const
{
    return name;
}

int RPG::getHealth() const
{
    return health;
}

int RPG::getStrength() const
{
    return strength;
}

int RPG::getDefense() const
{
    return defense;
}
