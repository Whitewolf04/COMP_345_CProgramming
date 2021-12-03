#ifndef PLAYER_H
#define PLAYER_H

class Map;
class Cards;
class Order;
class PlayerStrategy;
class Territory;
class Hand;
class OrdersList;

#include <vector>
using std::vector;
#include <ostream>
using std::ostream;
#include <string>
using std::string;
#include "PlayerStrategies.h"

class Player {
public:
    vector<Territory*> playerTerritories;
    Hand* playerHand;
    OrdersList* playerOrdersList;

    vector<Territory*> territoriesToDefend;
    vector<Territory*> territoriesToAttack;

    // Constructor
    Player();
    Player(string name);
    Player(Player& anotherPlayer);
    Player(string name, PlayerStrategy* ps);
    Player(string name, PlayerStrategy* ps, string strat);

    // Destructor
    ~Player();

    // Accessor
    string getPlayerName();
    int getReinArmy();
    int getId();
    string getStrategy();


    // Mutator
    void addReinArmy(int num);
    void removeReinArmy(int num);
    void setPlayerStrategy(PlayerStrategy* ps);
    void setStrategy(string strat);

    vector<Territory*> toDefend(); 
    vector<Territory*> toAttack();
    void issueOrder(Order* o);
private :
    string playerName;
    int reinArmy;
    int id;
    static int obj_count;
    friend ostream& operator<<(ostream&, const Player&);
    PlayerStrategy* ps;
    string strategy;
    
};

#endif //PLAYER_PLAYER_H