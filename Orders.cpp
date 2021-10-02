#include "Orders.h"

//Define Order functions
std::string Order::getName(){
    return name;
}


std::ostream& operator<<(std::ostream &strm, const Order &order){
    return strm << "inside list" << ' ';
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
    return *Order_List.front(); 
}

void OrdersList::move(){
    
}

void OrdersList::remove(int index){  
    Order_List.erase(Order_List.begin()+index);
}

std::ostream& operator<<(std::ostream &strm, const OrdersList &olist){
    std::cout << "OrderList contains:";
    for (int i=0; i<olist.Order_List.size(); ++i){
        std::cout << ' ' << olist.Order_List[i]->getName();
    }    
    std::cout << '\n';
    return std::cout << "";
}


//Define Order functions
