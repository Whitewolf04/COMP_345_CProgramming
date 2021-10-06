#include "Orders.h"
#include<string>

//Define Order functions
Order::Order(){
    type = "Order not specified";
}
Order::Order(std::string newType){
    type = newType;
}
std::string Order::getType(){
    return type;
}

void Order::validate(){
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

void Deploy::validate(){
    std::cout << this->getType()+"'s validation is not yet implemented" << "\n";
}

std::string Deploy::execute(){
    this->validate();
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Deploy &deploy){
    return strm << "Deploy ..." << ' ';
}

//Advance functions
Advance::Advance():Order("advance"){}


void Advance::validate(){
    std::cout << this->getType() << "'s validation is not yet implemented" << "\n";
}

std::string Advance::execute(){
    this->validate();
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Advance &advance){
    return strm << "Advance ..." << ' ';
}
//Bomb functions
Bomb::Bomb():Order("bomb"){}

void Bomb::validate(){
    std::cout << this->getType() << "'s validation is not yet implemented" << "\n";
}

std::string Bomb::execute(){
    this->validate();
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Bomb &bomb){
    return strm << "Bomb ..." << ' ';
}

//Blockade functions
Blockade::Blockade():Order("blockade"){}

void Blockade::validate(){
    std::cout << this->getType() << "'s validation is not yet implemented" << "\n";
}

std::string Blockade::execute(){
    this->validate();
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Blockade &blockade){
    return strm << "Blockade ..." << ' ';
}

//Airlift functions
Airlift::Airlift():Order("airlift"){}

void Airlift::validate(){
    std::cout << this->getType() << "'s validation is not yet implemented" << "\n";
}

std::string Airlift::execute(){
    this->validate();
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Airlift &airlift){
    return strm << "Airlift ..." << ' ';
}

//Negotiate functions
Negotiate::Negotiate():Order("negotiate"){}

void Negotiate::validate(){
    std::cout << this->getType() << "'s validation is not yet implemented" << "\n";
}

std::string Negotiate::execute(){
    this->validate();
    return this->getType()+"'s execution is not yet implemented";
}

std::ostream& operator<<(std::ostream &strm, const Negotiate &negotiate){
    return strm << "Negotiate ..." << ' ';
}


//Define OrderList functions
OrdersList::OrdersList(){
    Order_List;
}

OrdersList::OrdersList(const OrdersList &o){
    Order_List = o.Order_List;
}

OrdersList& OrdersList::operator =(const OrdersList &o){

    Order_List = o.Order_List;

    return *this;
}

void OrdersList::add(Order o){
    Order* ptr = &o;
    Order_List.push_back(ptr);
}

Order OrdersList::getElement(int index){
    return Order_List[index]->getType(); 
}

void OrdersList::move(int from, int to){
    Order buffer = *Order_List[from];
    *Order_List[from] = *Order_List[to];
    *Order_List[to] = buffer;
    return;
}

void OrdersList::remove(int index){  
    //Order ptr = *Order_List[index];
    Order_List.erase(Order_List.begin()+index);
}

std::ostream& operator<<(std::ostream &strm, const OrdersList &olist){
    std::cout << "OrderList contains:";
    for (int i=0; i<olist.Order_List.size(); ++i){
        std::cout << ' ' << olist.Order_List[i]->getType();
    }    
    return std::cout << "";
}

