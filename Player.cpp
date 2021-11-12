#include "Player.h"

vector<Player*> Player::playerList = vector<Player*>();

// Constructor
Player::Player(){
    playerName = "NULL";
    reinArmy = 0;
    playerHand = Hand();
    playerOrdersList = OrdersList();
    playerTerritories = vector<Territory*>();
}

Player::Player(string playerName){
    this->playerName = playerName;
    reinArmy = 0;
    playerHand = Hand();
    playerOrdersList = OrdersList();
    playerTerritories = vector<Territory*>();
}

Player::Player(Player& anotherPlayer){
    this->playerName = anotherPlayer.playerName;
    this->reinArmy = anotherPlayer.reinArmy;
    this->playerHand = Hand(anotherPlayer.playerHand);
    this->playerOrdersList = OrdersList(anotherPlayer.playerOrdersList);
    this->playerTerritories = vector<Territory*>();
    for(int i = 0; i < anotherPlayer.playerTerritories.size(); i++){
        this->playerTerritories.push_back(anotherPlayer.playerTerritories.at(i));
    }
}


// Destructor
Player::~Player(){
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

Player& Player::getPlayer(int index) {
    return *playerList.at(index);
}

int Player::getListSize() {
    return playerList.size();
}


// Mutator
void Player::addReinArmy(int num){
    reinArmy += num;
}

void Player::removeReinArmy(int num) {
    reinArmy -= num;
}

void Player::addPlayer(Player& player){
    playerList.push_back(&player);
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
    playerOrdersList.add(o);
}






