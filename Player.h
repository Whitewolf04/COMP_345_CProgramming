#ifndef PLAYER_H
#define PLAYER_H

class Map;
class Cards;
class Orders;
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
    Player(PlayerStrategy* ps);

    // Destructor
    ~Player();

    // Accessor
    string getPlayerName();
    int getReinArmy();
    int getId();

    // Mutator
    void addReinArmy(int num);
    void removeReinArmy(int num);
    void setPlayerStrategy(PlayerStrategy* ps);

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
    
};

#endif //PLAYER_PLAYER_H