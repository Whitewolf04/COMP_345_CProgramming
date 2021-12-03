#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include "Map.h"

#include <vector>
#include <ostream>
using std::cout;


void PlayerStrategy::setPlayer(Player* pl){
    this->p = pl;
}

Player* PlayerStrategy::getPlayer(){
    return p;
}

//HUMAN

 
void Human::issueOrder(Order* o){
    getPlayer()->playerOrdersList->add(o);
}

void Human::toAttack(){
    getPlayer()->territoriesToAttack.clear();

    for(int i=0; i < getPlayer()->playerTerritories.size(); i++){


        for(int j=0; j < getPlayer()->playerTerritories.at(i)->getEdges().size(); j++){
            
            if(getPlayer()->playerTerritories[i]->getEdges().at(j)->getPlayerNumber() != getPlayer()->getId()){

                getPlayer()->territoriesToAttack.push_back(getPlayer()->playerTerritories[i]->getEdges().at(j));

            }

        }
    }
}

void Human::toDefend(){
    getPlayer()->territoriesToDefend.clear();

}

//NEUTRAL
void Neutral::issueOrder(Order* o){
    cout << "A neutral player cannot issue order" << '\n';
}

void Neutral::toAttack(){
    getPlayer()->territoriesToAttack.clear();
}

void Neutral::toDefend(){
    getPlayer()->territoriesToDefend.clear();
}

//AGGRESSIVE
void Aggressive::issueOrder(Order* o){
    toAttack();
    toDefend();
    if(o->getType() == "deploy"){
        o = new Deploy(getPlayer()->getReinArmy(),getPlayer()->territoriesToDefend.at(0) , getPlayer()->getId());
        getPlayer()->playerOrdersList->add(o);
        cout << "Deployed to strongest country" << '\n';
    }else if(o->getType() == "advance"){
        
        o = new Advance(getPlayer()->territoriesToDefend.back(),getPlayer()->territoriesToDefend.at(0) , getPlayer()->getId());
        getPlayer()->playerOrdersList->add(o);

        //attack
        for(int i=0; i < getPlayer()->playerTerritories.size(); i++){
            for(int j=0; j < getPlayer()->territoriesToAttack.size(); j++){
                o = new Advance(getPlayer()->playerTerritories.at(i),getPlayer()->territoriesToAttack.at(j) , getPlayer()->getId());
                if(o->validate()){
                    getPlayer()->playerOrdersList->add(o);
                }
            }
        }

    }else{
        getPlayer()->playerOrdersList->add(o);
    }
}

void Aggressive::toAttack(){
    getPlayer()->territoriesToAttack.clear();
    for(int i=0; i < getPlayer()->playerTerritories.size(); i++){


        for(int j=0; j < getPlayer()->playerTerritories.at(i)->getEdges().size(); j++){
            
            if(getPlayer()->playerTerritories[i]->getEdges().at(j)->getPlayerNumber() != getPlayer()->getId()){

                getPlayer()->territoriesToAttack.push_back(getPlayer()->playerTerritories[i]->getEdges().at(j));

            }

        }
    }
}

void Aggressive::toDefend(){
    
    getPlayer()->territoriesToDefend.clear();
    
    int strongest_army = -1;
    int strongest_country = -1;

    //strongest country
    for(int i=0;i<getPlayer()->playerTerritories.size();i++){
        if(getPlayer()->playerTerritories.at(i)->getNumOfArmies() > strongest_army){
            strongest_army = getPlayer()->playerTerritories.at(i)->getNumOfArmies();
            strongest_country = i;
        }    
    }

    if(strongest_country != -1){
        getPlayer()->territoriesToDefend.push_back(getPlayer()->playerTerritories.at(strongest_country));
    }else{
        getPlayer()->territoriesToDefend.push_back(getPlayer()->playerTerritories.at(0));
    }


}

//BENEVOLENT
void Benevolent::issueOrder(Order* o){
    toDefend();
    if(o->getType() == "deploy"){
        o = new Deploy(getPlayer()->getReinArmy(),getPlayer()->territoriesToDefend.at(0) , getPlayer()->getId());
        getPlayer()->playerOrdersList->add(o);
    }else if(o->getType() == "advance"){
        o = new Advance(getPlayer()->territoriesToDefend.back(),getPlayer()->territoriesToDefend.at(0) , getPlayer()->getId());
        getPlayer()->playerOrdersList->add(o);
    }else{
        getPlayer()->playerOrdersList->add(o);
    }
}

void Benevolent::toAttack(){
    getPlayer()->territoriesToAttack.clear();
}

void Benevolent::toDefend(){
    //clear buffer
    getPlayer()->territoriesToDefend.clear();

    getPlayer()->territoriesToDefend.push_back(getPlayer()->playerTerritories.at(0));

    //make list of weakest countries
    for(int i=1; i<getPlayer()->playerTerritories.size(); i++){
        int smaller = -1;

        for(int j=0; j<getPlayer()->territoriesToDefend.size(); j++){
            if(getPlayer()->playerTerritories.at(i)->getNumOfArmies() <= getPlayer()->territoriesToDefend.at(j)->getNumOfArmies()){
                smaller = j;
            }

            std::vector<Territory*>::iterator it;
            it = getPlayer()->territoriesToDefend.begin()+j;

            if(smaller == -1){
                getPlayer()->territoriesToDefend.push_back(getPlayer()->playerTerritories.at(i));
            }else{
                getPlayer()->territoriesToDefend.insert(it, getPlayer()->playerTerritories.at(i));
            }
        }

    }
}

//CHEATER
void Cheater::issueOrder(Order* o){
    toAttack();
    for(int i=0; i<getPlayer()->territoriesToAttack.size(); i++){
        getPlayer()->territoriesToAttack.at(i)->setPlayerNumber(getPlayer()->getId());
        getPlayer()->playerTerritories.push_back(getPlayer()->territoriesToAttack.at(i));
    }
    cout << getPlayer()->getPlayerName() << " took ownership of all adjacent territories!!!!!!!!! ඞ" << '\n'; 
}

void Cheater::toAttack(){
    
    getPlayer()->territoriesToAttack.clear();
    
    for(int i=0; i < getPlayer()->playerTerritories.size(); i++){

        for(int j=0; j < getPlayer()->playerTerritories.at(i)->getEdges().size(); j++){
            if(getPlayer()->playerTerritories[i]->getEdges().at(j)->getPlayerNumber() != getPlayer()->getId()){

                getPlayer()->territoriesToAttack.push_back(getPlayer()->playerTerritories[i]->getEdges().at(j));


            }

        }
    }

}

void Cheater::toDefend(){
    getPlayer()->territoriesToDefend.clear();
}

