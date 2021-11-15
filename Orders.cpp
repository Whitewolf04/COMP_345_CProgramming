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

Order::Order(std::string newType, int _executor_id){
    type = newType;
    executor_id = _executor_id;
}

Order::Order(std::string newType, int _executor_id, Hand* cards){
    type = newType;
    executor_id = _executor_id;
    player_hand = cards;
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

int Order::getExecId(){
    return executor_id;
}

Hand* Order::getPlayerHand(){
    return player_hand;
}

bool Order::validate(){
    return false;
}

std::string Order::execute(){
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Order &order){
    return strm << "Order is an undefined order" << ' ';
}


//Deploy functions
Deploy::Deploy():Order("deploy"){}

Deploy::Deploy(int army_count, Territory* _target, int executor_id):Order("deploy", executor_id){
    this->army_count = army_count;
    target = _target;
}

bool Deploy::validate(){
    return getExecId() == target->getPlayerNumber();
}

std::string Deploy::execute(){

    if(!(this->validate())){
        return "Invalid Execution of Deploy";
    }else{
        target->setNumArmies(target->getNumOfArmies()+army_count);
        notify(this);
        return "Execution complete";
    }

}

std::ostream& operator<<(std::ostream &strm, const Deploy &deploy){
    return strm << "Deploy tells a certain number of armies taken from the reinforcement pool to deploy to a target territory owned by the player issuing this order." << ' ';
}


//Advance functions
Advance::Advance():Order("advance"){}

Advance::Advance(Territory* _source, Territory* _adjacent, int executor_id, Hand* player_hand):Order("advance", executor_id, player_hand){
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

    return getExecId() == source->getPlayerNumber() && neighbor;
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
                getPlayerHand()->add(new Cards("airlift"));

            }

        }
        notify(this);
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Advance &advance){
    return strm << "Advance tells a certain number of army units to move from a source territory to a target adjacent territory." << ' ';
}

//Airlift functions
Airlift::Airlift():Order("airlift"){}

Airlift::Airlift(int army_count, Territory* _source, Territory* _target, int executor_id, Hand* player_hand):Order("airlift", executor_id, player_hand){
    this->army_count = army_count;
    source = _source;
    target = _target;
}

bool Airlift::validate(){
    return source->getPlayerNumber() == target->getPlayerNumber() == getExecId() && getPlayerHand()->contains("airlift"); //needs to be created with an airlift card
}

std::string Airlift::execute(){
    if(!(this->validate())){
        return "Invalid Execution of Airlift";
    }else{
        //play card
        getPlayerHand()->playCard("airlift");

        source->setNumArmies(source->getNumOfArmies()-army_count);
        target->setNumArmies(target->getNumOfArmies()+army_count);
        notify(this);
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Airlift &airlift){
    return strm << "An airlift order tells a certain number of armies taken from a source territory to be moved to a target territory, the source and the target territory being owned by the player issuing the order. The airlift order can only be created by playing the airlift card." << ' ';
}

//Bomb functions
Bomb::Bomb():Order("bomb"){}

Bomb::Bomb(Territory* _source, Territory* _adjacent, int executor_id, Hand* player_hand):Order("bomb", executor_id, player_hand){
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
    return adjacent->getPlayerNumber() != getExecId() && neighbor && getPlayerHand()->contains("bomb"); //player must use bomb card
}

std::string Bomb::execute(){
    if(!this->validate()){
        return "Invalid Execution of Airlift";
    }else{
        getPlayerHand()->playCard("bomb");

        adjacent->setNumArmies(adjacent->getNumOfArmies()/2);
        notify(this);
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Bomb &bomb){
    return strm << "A bomb order targets a territory owned by another player than the one issuing the order. Its result is to remove half of the armies from this territory. The bomb order can only be created by playing the bomb card. " << ' ';
}

//Blockade functions
Blockade::Blockade():Order("blockade"){}

Blockade::Blockade(Territory* _target, int executor_id, Hand* player_hand):Order("blockade", executor_id, player_hand){
    target = _target;
}

bool Blockade::validate(){
    return target->getPlayerNumber() == getExecId() && getPlayerHand()->contains("blockade"); //must use blockade card
}

std::string Blockade::execute(){
    if(!this->validate()){
        return "Invalid Execution of Blockade";
    }else{
        getPlayerHand()->playCard("blockade");

        target->setNumArmies(target->getNumOfArmies()*2);
        //send territory to Neutral player
        notify(this);
        return "Execution complete";
    }
}

std::ostream& operator<<(std::ostream &strm, const Blockade &blockade){
    return strm << "A blockade order targets a territory that belongs to the player issuing the order. Its effect is todouble the number of armies on the territory and to transfer the ownership of the territory to the Neutral player. The blockade order can only be created by playing the blockade card." << ' ';
}


//Negotiate functions
Negotiate::Negotiate():Order("negotiate"){}

Negotiate::Negotiate(int _target_id, int executor_id, Hand* player_hand):Order("negotiate", executor_id, player_hand){
    target_id = _target_id;
}

bool Negotiate::validate(){
    return getExecId() != target_id && getPlayerHand()->contains("diplomacy"); //must use diplomacy card
}

std::string Negotiate::execute(){
    if(!this->validate()){
        return "Invalid Execution of Negotiate";
    }else{
        getPlayerHand()->playCard("diplomacy");

        //nullify any attack between executor and target Player
        notify(this);
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

//Copy constructors
OrdersList::OrdersList(const OrdersList &o){
    cout << "\tDEBUG: Order List copy constructor is called" << endl;
    for (int i=0; i<o.Order_List.size(); ++i){
        if(o.Order_List[i]->getType() == "advance"){
            Advance * newOrder = new Advance();
            Order_List.push_back(newOrder);
        } else if(o.Order_List[i]->getType() == "deploy"){
            Deploy * newOrder = new Deploy();
            Order_List.push_back(newOrder);
        } else if(o.Order_List[i]->getType() == "bomb"){
            Bomb * newOrder = new Bomb();
            Order_List.push_back(newOrder);
        } else if(o.Order_List[i]->getType() == "blockade"){
            Blockade * newOrder = new Blockade();
            Order_List.push_back(newOrder);
        } else if(o.Order_List[i]->getType() == "airlift"){
            Airlift * newOrder = new Airlift();
            Order_List.push_back(newOrder);
        } else if(o.Order_List[i]->getType() == "negotiate"){
            Negotiate * newOrder = new Negotiate();
            Order_List.push_back(newOrder);
        }
    }
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
    notify(this);
}

//get the order type
Order* OrdersList::getElement(int index){
    return Order_List[index];
}

//get list size
int OrdersList::getSize(){
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

//String to logs implementations
void OrdersList::stringToLog() {
    fstream filestream;
    filestream.open("gamelog.txt", ios::app);
    filestream << Order_List.back()->getType() << " was added to Player number " << Order_List.back()->getExecId() << "'s list"<< '\n';
    filestream.close();
};

void Order::stringToLog() {
    fstream filestream;
    filestream.open("gamelog.txt", ios::app);
    filestream << this->getType() << " is executed by player " << this->getExecId() << "\n";
    filestream.close();
};