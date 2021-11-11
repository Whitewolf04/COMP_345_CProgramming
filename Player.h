#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
    vector<Territory> playerTerritories;
    Hand playerHand;
    OrdersList playerOrdersList;

    // Constructor
    Player();
    Player(string name);

    // Accessor
    string getPlayerName();
    int getReinArmy();

    // Mutator
    void addReinArmy(int num);
    void removeReinArmy(int num);

    vector<Territory>* toDefend();
    vector<Territory>* toAttack();
    void issueOrder(Order o);
private :
    string playerName;
    int reinArmy;
};

#endif //PLAYER_PLAYER_H