#include "Player.h"
#include <iostream>

int Player::obj_count = 0;

// Constructor
Player::Player(){
//    cout << "DEBUG: Default Player constructor was called" << endl;
    id = obj_count;
    obj_count++;
    playerName = "NULL";
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
}

Player::Player(string playerName){
//    cout << "DEBUG: String Player constructor was called" << endl;
    id = obj_count;
    obj_count++;
    this->playerName = playerName;
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
}

Player::Player(Player& anotherPlayer){
    id = obj_count;
    obj_count++;
//    cout << "DEBUG: Player copy constructor is called" << endl;
    this->playerName = anotherPlayer.playerName;
    this->reinArmy = anotherPlayer.reinArmy;
//    cout << "DEBUG: This player " << this->playerName << " reinArmy: " << this->reinArmy << endl;
//    cout << "DEBUG: Another player " << anotherPlayer.playerName << " reinArmy " << anotherPlayer.reinArmy << endl;
    this->playerHand = new Hand(*anotherPlayer.playerHand);
    this->playerOrdersList = new OrdersList(*anotherPlayer.playerOrdersList);
    this->playerTerritories = vector<Territory*>();
    for(int i = 0; i < anotherPlayer.playerTerritories.size(); i++){
        this->playerTerritories.push_back(anotherPlayer.playerTerritories.at(i));
    }
}


// Destructor
Player::~Player(){
//    cout << "DEBUG: Player " << this->playerName << " destructor is called" << endl;
//    cout << "DEBUG: This player has " << this->reinArmy << " number of army" << endl;
//    cout << "DEBUG: playerOrdersList address: " << playerOrdersList << endl;
    free(playerOrdersList);
    playerOrdersList = nullptr;
    free(playerHand);
    playerHand = nullptr;
//    cout << "DEBUG: playerOrdersList destruction complete" << endl;
//    cout << "DEBUG: Player destructor completes" << endl;
}

// Print out function
ostream& operator<<(ostream &strm, const Player& player){
    strm << "Player " << player.playerName;
    return strm << "";
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
    Territory dummy1 = Territory();
    Territory dummy2 = Territory();
    territoriesToDefend.push_back(&dummy1);
    territoriesToDefend.push_back(&dummy2);
    // add computation for territories to defend
    return territoriesToDefend;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> territoriesToAttack = vector<Territory*>();
    Territory dummy1 = Territory();
    Territory dummy2 = Territory();
    territoriesToAttack.push_back(&dummy1);
    territoriesToAttack.push_back(&dummy2);
    // add computation for territories to defend
    return territoriesToAttack;
}

void Player::issueOrder(Order& o) {
//    cout << "DEBUG: Order " << o << " is being issued" << endl;
    (*playerOrdersList).add(&o);
//    cout << "DEBUG: Order " << o << " has been issued from Player" << endl;
}

int Player::getId() {
    return id;
}