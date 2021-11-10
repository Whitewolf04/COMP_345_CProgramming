#include "Player.h"
#include <iostream>
using namespace std;

int main() {
    // Initialize all the cards
    Cards bomb = Cards("bomb");
    Cards reinforcement = Cards("reinforcement");
    Cards blockade = Cards("blockade");
    Cards airlift = Cards("airlift");
    Cards diplomacy = Cards("diplomacy");

    // Initialize some territories
    Territory t1 = Territory(1, 0, "t1", 1);
    Territory t2 = Territory(2, 0, "t2", 1);
    Territory t3 = Territory(3, 0, "t3", 1);
    Territory t4 = Territory(4, 0, "t4", 1);

    // Initialize Player hand
    Hand hand = Hand(5);

    // Initialize Order list
    OrdersList orders = OrdersList();

    // Initialize list of territories
    vector<Territory*> territories = vector<Territory*>();
    territories.push_back(&t1);
    territories.push_back(&t2);
    territories.push_back(&t3);
    territories.push_back(&t4);

    // Initialize the Player
    Player player = Player(territories, hand, orders, 1, 0);
    player.addCards(&bomb);
    player.addCards(&reinforcement);
    player.addCards(&blockade);
    player.addCards(&airlift);
    player.addCards(&diplomacy);

    cout << player << endl;

    Player::playerList.push_back(&player);
    cout << "Player added to player list" << endl;

    return 0;
}