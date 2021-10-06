#include "Orders.cpp"


int main(){
    
    Advance order1;
    Airlift order2;
    Negotiate order3;
    OrdersList list;

    //validation and execution of orders
    order2.validate();
    
    list.add(order1);    
    list.add(order2);
    list.add(order3);

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
    

}