
#include "Player.h"
using namespace std;

Player::Player(){
    territories = vector<Territory*>();
    hand = Hand();
    orders = OrdersList();
}

Player::Player(vector<Territory*>& t, Hand& h, OrdersList& o){
    territories = t;
    hand = h;
    orders = o;
}

Player::Player(const Player& p){
    this->territories = p.territories;
    this->hand = p.hand;
    this->orders = p.orders;
}

Player::~Player(){
    for(int i = 0; i < territories.size(); i++){
        delete territories[i];
    }
}

std::ostream& operator<<(ostream& stream, const Player &player){
    stream << "Player hand:\n" << player.hand;
    stream << "\nPlayer territories:\n";
    for(int i = 0; i < player.territories.size(); i++){
        stream << *player.territories[i] << "\n";
    }
    stream << "\nPlayer orders list:\n" << player.orders;
}

void Player::addTerritories(Territory *t){
    territories.push_back(t);
}

void Player::addCards(Cards *c){
    hand.add(c);
}

void Player::addOrder(Order *o){
    orders.add(*o);
}

vector<Territory*>* Player::toDefend() {
    return &territories;
}

vector<Territory*>* Player::toAttack(){
    return &territories;
}

void Player::issueOrder(){
    Order order = Order();
    orders.add(order);
}



