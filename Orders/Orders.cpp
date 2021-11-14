#include "Orders.h"
#include<string>

//Define Order functions

//constructors
Order::Order(){
    type = "Order not specified";
}
Order::Order(std::string newType){
    type = newType;
}

Order::Order(std::string newType, Player* executor){
    type = newType;
}

Order::Order(const Order &o){
    this->type = o.type;
}

Order& Order::operator =(const Order &o){

    this->type = o.type;

    return *this;
}

//Order functions
std::string Order::getType(){
    return type;
}

Player* Order::getPlayer(){
    return executor;
}

bool Order::validate(){
    std::cout << this->getType()+"'s validation is not yet implemented" << "\n";
}

std::string Order::execute(){
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Order &order){
    return strm << "Order is an undefined order" << ' ';
}


//Deploy functions
Deploy::Deploy():Order("deploy"){}

Deploy::Deploy(int army_count, Territory* _target, Player* executor):Order("deploy", executor){
    this->army_count = army_count;
    target = _target;
}

bool Deploy::validate(){
    return getPlayer()->getId() == target->getPlayerNumber();
}

std::string Deploy::execute(){

    if(!(this->validate())){
        return "Invalid Execution of Deploy";
    }else{
        target->setNumArmies(target->getNumOfArmies()+army_count);
        return "Execution complete";
    }

}

std::ostream& operator<<(std::ostream &strm, const Deploy &deploy){
    return strm << "Deploy tells a certain number of armies taken from the reinforcement pool to deploy to a target territory owned by the player issuing this order." << ' ';
}


//Advance functions
Advance::Advance():Order("advance"){}

Advance::Advance(Territory* _source, Territory* _adjacent, Player* executor):Order("advance", executor){
    source = _source;
    adjacent = _adjacent;
}

bool Advance::validate(){
    bool neighbor = false;
    for(int i=0; i<source->getTerritoryConnexions().size(); i++){
        if(source->getTerritoryConnexions().at(i) == adjacent->getTerritoryNumber()){
            neighbor = true;
        }
    }

    return getPlayer()->getId() == source->getPlayerNumber() && neighbor;
}

int deathCalculation(int qty, double probability){
    bool kill;
    int dead = 0;
    while(--qty != 0){
        kill = (rand() % 100) < probability*100;
        if(kill){
            dead++;
        }
    }
    return dead;
}

std::string Advance::execute(){
    if(!this->validate()){
        return "Invalid Execution of Advance";
    }else{

        if(source->getPlayerNumber() == adjacent->getPlayerNumber()){
            adjacent->setNumArmies(source->getNumOfArmies());
            source->setNumArmies(0);
        }else{
            //defense
            source->setNumArmies(source->getNumOfArmies()-deathCalculation(adjacent->getNumOfArmies(),0.7));
            //attack
            adjacent->setNumArmies(adjacent->getNumOfArmies()-deathCalculation(source->getNumOfArmies(),0.6));
            if(adjacent->getNumOfArmies() == 0){
                //conquer territory
                //receive card.
            }
        }

    }
}

std::ostream& operator<<(std::ostream &strm, const Advance &advance){
    return strm << "Advance tells a certain number of army units to move from a source territory to a target adjacent territory." << ' ';
}

//Airlift functions
Airlift::Airlift():Order("airlift"){}

Airlift::Airlift(int army_count, Territory* _source, Territory* _target, Player* executor):Order("airlift", executor){
    this->army_count = army_count;
    source = _source;
    target = _target;
}

bool Airlift::validate(){
    return source->getPlayerNumber() == target->getPlayerNumber() == getPlayer()->getId(); //needs to be created with an airlift card
}

std::string Airlift::execute(){
    if(!(this->validate())){
        return "Invalid Execution of Airlift";
    }else{
        source->setNumArmies(source->getNumOfArmies()-army_count);
        target->setNumArmies(target->getNumOfArmies()+army_count);
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Airlift &airlift){
    return strm << "An airlift order tells a certain number of armies taken from a source territory to be moved to a target territory, the source and the target territory being owned by the player issuing the order. The airlift order can only be created by playing the airlift card." << ' ';
}

//Bomb functions
Bomb::Bomb():Order("bomb"){}

Bomb::Bomb(Territory* _source, Territory* _adjacent, Player* executor):Order("bomb", executor){
    source = _source;
    adjacent = _adjacent;
}

bool Bomb::validate(){
    bool neighbor = false;
    for(int i=0; i<source->getTerritoryConnexions().size(); i++){
        if(source->getTerritoryConnexions().at(i) == adjacent->getTerritoryNumber()){
            neighbor = true;
        }
    }
    return adjacent->getPlayerNumber() != getPlayer()->getId() && neighbor; //player must use bomb card
}

std::string Bomb::execute(){
    if(!this->validate()){
        return "Invalid Execution of Airlift";
    }else{
        adjacent->setNumArmies(adjacent->getNumOfArmies()/2);
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Bomb &bomb){
    return strm << "A bomb order targets a territory owned by another player than the one issuing the order. Its result is to remove half of the armies from this territory. The bomb order can only be created by playing the bomb card. " << ' ';
}

//Blockade functions
Blockade::Blockade():Order("blockade"){}

Blockade::Blockade(Territory* _target, Player* executor):Order("blockade", executor){
    target = _target;
}

bool Blockade::validate(){
    return target->getPlayerNumber() == getPlayer()->getId(); //must use blockade card
}

std::string Blockade::execute(){
    if(!this->validate()){
        return "Invalid Execution of Blockade";
    }else{
        target->setNumArmies(target->getNumOfArmies()*2);
        //send territory to Neutral player
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Blockade &blockade){
    return strm << "A blockade order targets a territory that belongs to the player issuing the order. Its effect is todouble the number of armies on the territory and to transfer the ownership of the territory to the Neutral player. The blockade order can only be created by playing the blockade card." << ' ';
}


//Negotiate functions
Negotiate::Negotiate():Order("negotiate"){}

Negotiate::Negotiate(Player* _target, Player* executor):Order("negotiate", executor){
    target = _target;
}

bool Negotiate::validate(){
    return getPlayer()->getId() != target->getId(); //must use diplomacy card
}

std::string Negotiate::execute(){
    if(!this->validate()){
        return "Invalid Execution of Negotiate";
    }else{
        //nullify any attack between executor and target Player
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Negotiate &negotiate){
    return strm << "A negotiate order targets an enemy player. It results in the target player and the player issuingthe order to not be able to successfully attack each others’ territories for the remainder of the turn. The negotiate order can only be created by playing the diplomacy card." << ' ';
}


//Define OrderList constructors and destructor
OrdersList::OrdersList(){
    Order_List;
}

/*
//Copy constructors
OrdersList::OrdersList(const OrdersList &o){

    Order* _arr = new Order[o.Order_List.size()];

    for (int i=0; i<o.Order_List.size(); ++i){
        _arr[i] = *o.Order_List[i];
        Order_List.push_back(&_arr[i]);
    }
}

OrdersList& OrdersList::operator =(const OrdersList &o){

    Order* ptr = new Order[o.Order_List.size()];

    for (int i=0; i<o.Order_List.size(); ++i){
        ptr[i] = *o.Order_List[i];
        this->Order_List.push_back(&ptr[i]);
    }

    return *this;
}
*/
//Destructor: deletes all Order pointer of the list
OrdersList::~OrdersList(){
    for (int i=0; i<Order_List.size(); ++i){
        delete Order_List[i];
    }
}

//Order List functions


//adds Order pointer to the vector list
void OrdersList::add(Order* o){
    Order_List.push_back(o);
}

//get the order type
Order* OrdersList::getElement(int index){
    return Order_List[index];
}

int OrdersList::getSize() {
    return Order_List.size();
}

//swaps values of two order pointers in the list at different positions
void OrdersList::move(int from, int to){
    std::swap(Order_List[to],Order_List[from]);
    return;
}

//removes element from the list
void OrdersList::remove(int index){
    Order_List.erase(Order_List.begin()+index);
}

//Shows all element of the list
std::ostream& operator<<(std::ostream &strm, const OrdersList &olist){
    std::cout << "OrderList contains:";
    for (int i=0; i<olist.Order_List.size(); ++i){
        std::cout << ' ' << olist.Order_List[i]->getType();
    }
    return std::cout << "";
}
