#include "Player.h"
using namespace std;

Player::Player(){
    this->p_num = -1;
    reinArmy = 0;
    territories = vector<Territory*>();
    hand = Hand();
    orders = OrdersList();
}

Player::Player(int pNum){
    this->p_num = pNum;
    reinArmy = 0;
    territories = vector<Territory*>();
    hand = Hand();
    orders = OrdersList();
}

Player::Player(vector<Territory*>& t, Hand& h, OrdersList& o, int pNum, int reinArmy){
    territories = t;
    hand = h;
    orders = o;
    p_num = pNum;
    this->reinArmy = reinArmy;
}

Player::Player(const Player& p){
    this->territories = p.territories;
    this->hand = p.hand;
    this->orders = p.orders;
    this->p_num = p.p_num;
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
    return stream << "";
}


// Accessor methods declarations
vector<Territory*> Player::getTerritories() {
    return territories;
}

Hand& Player::getCards() {
    return hand;
}

OrdersList& Player::getOrders(){
    return orders;
}


// Mutator methods declarations
void Player::addTerritories(Territory *t){
    territories.push_back(t);
}

void Player::addCards(Cards *c){
    hand.add(c);
}

void Player::addOrder(Order *o){
    orders.add(*o);
}

void Player::setPlayerNum(int pNum) {
    p_num = pNum;
}

void Player::removeReinArmy(int remove){
    reinArmy -= remove;
}

void Player::addReinArmy(int add){
    reinArmy += add;
}


// Operation methods declaration
vector<Territory*>* Player::toDefend() {
    return &territories;
}

vector<Territory*>* Player::toAttack(){
    return &territories;
}

void Player::issueOrder(){
    Order order = Order();
    orders.add(order);
    cout << "Order added to the list of orders" << endl;
}



