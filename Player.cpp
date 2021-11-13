#include "Player.h"

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

void Player::issueOrder(Order* o) {
    playerOrdersList.add(o);
}

string Player::getName() {
    return name;
}

Player::Player(string n) {
    id = obj_count;
    obj_count++;
    
    name = n;
}
