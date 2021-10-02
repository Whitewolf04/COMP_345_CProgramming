#include "Orders.cpp"


int main(){

    
    Advance example1;
    Advance example2;
    OrdersList list;

    list.add(example1);    
    list.add(example2);
    std::cout << list << "\n";
    list.remove(0);
    //list->add(example2);
    std::cout << list << "\n";

}