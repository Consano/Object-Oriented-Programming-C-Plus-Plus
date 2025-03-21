#include "RPG.h"


void displayStats(RPG player1, RPG player2)
{
    printf("%s health: %d, %s health: %d\n", 
        player1.getName().c_str(), player1.getHealth(), 
        player2.getName().c_str(), player2.getHealth());
}

void displayEnd(RPG player1, RPG player2)
{
    if (player1.getHealth() != 0)
    {
        printf("%s wins!", player1.getName().c_str());
    }
    else
    {
        printf("%s wins!", player2.getName().c_str());
    }
}

void gameLoop(RPG* player1, RPG* player2)
{
    while(player1->getHealth() > 0 && player2->getHealth() > 0)
    {
        printf("%s's turn\n", player1->getName().c_str());
        player1->useSkill(player2);
        printf("-------------------------------------\n");

        printf("%s's turn\n", player2->getName().c_str());
        player2->useSkill(player1);
        printf("-------------------------------------\n");
    }
}


int main() {

    RPG p1("Wiz", 70, 45, 15, "mage");
    RPG p2;

    gameLoop(&p1, &p2);
    displayEnd(p1, p2);


    return 0;
}