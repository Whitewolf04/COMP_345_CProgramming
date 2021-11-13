#include "Orders.cpp"


int main(){
    
    std::cout << "Creating orders and list..." << "\n";

    //Create all orders
    Order* order1 = new Deploy();
    Order* order2 = new Advance();
    Order* order3 = new Bomb();
    Order* order4 = new Blockade();
    Order* order5 = new Airlift();
    Order* order6 = new Negotiate();

    //Create an order list
    OrdersList list;

    //validation of order
    std::cout << "Validating 2nd Order" << "\n";
    order2->validate();
    std::cout << "\n";

    //Adding order to list
    std::cout << "Adding orders to the list..." << "\n";
    list.add(order1);    
    list.add(order2);
    list.add(order3);
    list.add(order4);
    list.add(order5);
    list.add(order6);

    //Copying list using copy constructor
    std::cout << "Copying List..." << "\n";
    OrdersList list_copy = list;
    std::cout << "\n";

    //Executing 2nd order
    std::cout << "Executing 2nd order..." << "\n";
    std::cout << list.getElement(1)->execute() << "\n";
    std::cout << "\n";

    //iterate through the list
    std::cout << "Show list..." << "\n";
    std::cout << list << "\n";
    std::cout << "\n";

    std::cout << "Remove second order" << "\n";
    //remove second order
    list.remove(1);

    std::cout << "Show list..." << "\n";
    //iterate through the list
    std::cout << list << "\n";

    //swap orders on index 0 and 1
    std::cout << "Move 2nd Order to first..." << "\n";
    list.move(0,1);

    std::cout << "Show list..." << "\n";
    std::cout << list << "\n";

    std::cout << "Show copy of original list..." << "\n";
    std::cout << list_copy << "\n";

   
}