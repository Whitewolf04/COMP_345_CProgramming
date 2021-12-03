#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>

#include "Player.h"

int Player::obj_count = 0;

// Constructor
Player::Player(){
    id = obj_count;
    playerName = "NULL";
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
    territoriesToAttack = vector<Territory*>();
    territoriesToDefend = vector<Territory*>();
    obj_count++;
}

Player::Player(string playerName){
    id = obj_count;
    this->playerName = playerName;
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
    territoriesToAttack = vector<Territory*>();
    territoriesToDefend = vector<Territory*>();
    obj_count++;
}

Player::Player(Player& anotherPlayer){
//    cout << "DEBUG: Player Copy constructor is called " << endl;
    this->id = anotherPlayer.id;
//    cout << "Copied player's id" << endl;
    this->playerName = anotherPlayer.playerName;
    this->reinArmy = anotherPlayer.reinArmy;
    this->playerHand = new Hand(*anotherPlayer.playerHand);
    this->playerOrdersList = new OrdersList(*anotherPlayer.playerOrdersList);
    this->playerTerritories = vector<Territory*>();
    territoriesToAttack = vector<Territory*>();
    territoriesToDefend = vector<Territory*>();
    for(int i = 0; i < anotherPlayer.playerTerritories.size(); i++){
        this->playerTerritories.push_back(anotherPlayer.playerTerritories.at(i));
    }
    for(int i = 0; i < anotherPlayer.territoriesToAttack.size(); i++){
        this->territoriesToAttack.push_back(anotherPlayer.territoriesToAttack.at(i));
    }
    for(int i = 0; i < anotherPlayer.territoriesToDefend.size(); i++){
        this->territoriesToDefend.push_back(anotherPlayer.territoriesToDefend.at(i));
    }
    obj_count++;
}

Player::Player(string name, PlayerStrategy* ps){
    id = obj_count;
    this->playerName = name;
    this->ps = ps;
    ps->setPlayer(this);
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
    territoriesToAttack = vector<Territory*>();
    territoriesToDefend = vector<Territory*>();
    obj_count++;
}

Player::Player(string name, PlayerStrategy* ps, string strat){
    id = obj_count;
    this->playerName = name;
    this->ps = ps;
    ps->setPlayer(this);
    reinArmy = 0;
    playerHand = new Hand();
    playerOrdersList = new OrdersList();
    playerTerritories = vector<Territory*>();
    territoriesToAttack = vector<Territory*>();
    territoriesToDefend = vector<Territory*>();
    setStrategy(strat);
    obj_count++;
}

// Destructor
Player::~Player(){
    free(playerOrdersList);
    playerOrdersList = nullptr;
    free(playerHand);
    playerHand = nullptr;
    obj_count--;
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

int Player::getId(){
    return id;
}

string Player::getStrategy(){
    return strategy;
}


// Mutator
void Player::setStrategy(string strat){
    strategy = strat;
}

void Player::addReinArmy(int num){
    reinArmy += num;
}

void Player::removeReinArmy(int num) {
    reinArmy -= num;
}

void Player::setPlayerStrategy(PlayerStrategy* ps){
    this->ps = ps;
}

/*
// Operational methods
vector<Territory*> Player::toDefend() {
    vector<Territory*> territoriesToDefend = vector<Territory*>();
    Territory* dummy1 = new Territory();
    Territory* dummy2 = new Territory();
    territoriesToDefend.push_back(dummy1);
    territoriesToDefend.push_back(dummy2);
    // add computation for territories to defend
    return territoriesToDefend;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> territoriesToAttack = vector<Territory*>();
    Territory * dummy1 = new Territory();
    Territory * dummy2 = new Territory();
    territoriesToAttack.push_back(dummy1);
    territoriesToAttack.push_back(dummy2);
    // add computation for territories to defend
    return territoriesToAttack;
}

void Player::issueOrder(Order* o) {
    playerOrdersList->add(o);
}

*/

// Operational methods
vector<Territory*> Player::toDefend() {
    ps->toDefend();
    return territoriesToDefend;
}

vector<Territory*> Player::toAttack() {
    ps->toAttack();
    return territoriesToAttack;
}

void Player::issueOrder(Order* o) {
    ps->issueOrder(o);
}