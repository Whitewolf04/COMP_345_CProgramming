#include "Orders.cpp"


int main(){
    
    Deploy order1;
    Advance order2;
    Bomb order3;
    Blockade order4;
    Airlift order5;
    Negotiate order6;
    
    OrdersList list;


    //validation and execution of orders
    order2.validate();
    
    list.add(order1);    
    list.add(order2);
    list.add(order3);
    list.add(order4);
    list.add(order5);
    list.add(order6);

    OrdersList list_copy = list;

    std::cout << list.getElement(1).execute() << "\n";

    //iterate through the list
    std::cout << list << "\n";

    //remove first order
    list.remove(1);

    //iterate through the list
    std::cout << list << "\n";

    //move() not yet implemented
    list.move(0,1);

    std::cout << list << "\n";
    std::cout << list_copy << "\n";


}