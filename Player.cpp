#include "Player.h"

// Constructor
Player::Player(){
    playerName = "NULL";
}

Player::Player(string playerName){
    this->playerName = playerName;
}


// Accessor
string Player::getPlayerName(){
    return playerName;
}

int Player::getReinArmy(){
    return reinArmy;
}


// Mutator
void Player::addReinArmy(int num){
    reinArmy += num;
}

void Player::removeReinArmy(int num) {
    reinArmy -= num;
}


// Operational methods
vector<Territory>* Player::toDefend() {
    vector<Territory> * territoriesToDefend = new vector<Territory>();
    // add computation for territories to defend
    return territoriesToDefend;
}

vector<Territory>* Player::toAttack() {
    vector<Territory> * territoriesToAttack = new vector<Territory>();
    // add computation for territories to defend
    return territoriesToAttack;
}

void Player::issueOrder(Order o) {
    playerOrdersList.add(o);
}






