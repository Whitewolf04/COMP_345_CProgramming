#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
    Player(string n);
    string getName();
    int getId();
    vector<Territory> playerTerritories;
    Hand playerHand;
    OrdersList playerOrdersList;
    vector<Territory>* toDefend();
    vector<Territory>* toAttack();
    void issueOrder(Order* o);
private :
    string name;
    int id;
    static int obj_count;
};

#endif //PLAYER_PLAYER_H