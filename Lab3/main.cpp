#include "RPG.h"

int main() {

    RPG player1;
    RPG player2("Dave", 10, 10, 12, "mage");

    printf("Player1- name:%s, health:%d, strength:%d, defense:%d, alive:%d\n", 
        player1.getName().c_str(), player1.getHealth(), 
        player1.getStrength(), player1.getDefense(), 
        player1.isAlive());

    printf("Player2- name:%s, health:%d, strength:%d, defense:%d, alive:%d\n", 
        player2.getName().c_str(), player2.getHealth(), 
        player2.getStrength(), player2.getDefense(), 
        player2.isAlive());
    
    player2.updateHealth(32);
    printf("Player2 with updated health- name:%s, health:%d, strength:%d, defense:%d, alive:%d\n", 
        player2.getName().c_str(), player2.getHealth(), 
        player2.getStrength(), player2.getDefense(), 
        player2.isAlive());

    return 0;
}