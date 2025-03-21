#include "RPG.h"
#include <cstdlib>
#include <iostream>

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
    name = n;
    health = h;
    strength = s;
    defense = d;
    type = t;

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
    health = newHealth;
}

void RPG::attack(RPG* opponent)
{
    int newHealth = opponent->getHealth() - (strength - opponent->getDefense());
    opponent->updateHealth(newHealth);
}

void RPG::useSkill(RPG* opponent)
{
    for (size_t i = 0; i < 2; i++)
    {
        printf("Skill %i: %s\n", i, skills[i].c_str());
    }

    int chosen_skill_index = -1;

    while(chosen_skill_index != 0 && chosen_skill_index != 1)
    {
        printf("Choose a skill to use: Enter 0 or 1\n");
        cin >> chosen_skill_index;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    string chosen_skill = skills[chosen_skill_index];

    printAction(chosen_skill, *opponent);

    this->attack(opponent);
}

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
