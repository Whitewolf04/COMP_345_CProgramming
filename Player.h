#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
    static vector<Player*> playerList;
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
    static Player& getPlayer(int index);
    static int getListSize();

    // Mutator
    void addReinArmy(int num);
    void removeReinArmy(int num);
    static void addPlayer(Player& player);

    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(Order& o);
private :
    string playerName;
    int reinArmy;
    friend ostream& operator<<(ostream&, const Player&);
};

#endif //PLAYER_PLAYER_H