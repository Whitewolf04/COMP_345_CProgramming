#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
    Player(string n);
    string getName();
    vector<Territory> playerTerritories;
    Hand playerHand;
    OrdersList playerOrdersList;
    vector<Territory>* toDefend();
    vector<Territory>* toAttack();
    void issueOrder(Order o);
private :
    string name;
};

#endif //PLAYER_PLAYER_H