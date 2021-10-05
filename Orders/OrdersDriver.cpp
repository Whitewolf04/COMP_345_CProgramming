#include "Orders.cpp"


int main(){
    
    Advance order1;
    Airlift order2;
    OrdersList list;

    //validation and execution of orders
    order2.validate();
    std::cout << order1.execute() << "\n";

    list.add(order1);    
    list.add(order2);

    //iterate through the list
    std::cout << list << "\n";

    //remove first order
    list.remove(0);

    //move() not yet implemented

    std::cout << list << "\n";
    

}