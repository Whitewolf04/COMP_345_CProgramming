#include "Player.h"

vector<Player*> Player::playerList = vector<Player*>();

// Constructor
Player::Player(){
    playerName = "NULL";
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
}

Player::Player(string playerName){
    this->playerName = playerName;
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
}


// Destructor
Player::~Player(){
    free(playerHand);
    playerHand = NULL;
    free(playerOrdersList);
    playerOrdersList = NULL;

    for(int i = 0; i < playerList.size(); i++){
        free(playerList.at(i));
        playerList.at(i) = NULL;
    }
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
vector<Territory*> Player::toDefend() {
    vector<Territory*> territoriesToDefend = vector<Territory*>();
    // add computation for territories to defend
    return territoriesToDefend;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> territoriesToAttack = vector<Territory*>();
    // add computation for territories to defend
    return territoriesToAttack;
}

void Player::issueOrder(Order& o) {
    (*playerOrdersList).add(o);
}






