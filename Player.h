#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player{
public:
    vector<Territory*> playerTerritories;
    Hand* playerHand;
    OrdersList* playerOrdersList;

    // Constructor
    Player();
    Player(string name);
    Player(Player& anotherPlayer);

    // Destructor
    ~Player();

    // Accessor
    string getPlayerName();
    int getReinArmy();
    int getId();

    // Mutator
    void addReinArmy(int num);
    void removeReinArmy(int num);

    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(Order& o);
    static int obj_count;
private :
    string playerName;
    int reinArmy;
    friend ostream& operator<<(ostream&, const Player&);
    int id;
};

#endif //PLAYER_PLAYER_H