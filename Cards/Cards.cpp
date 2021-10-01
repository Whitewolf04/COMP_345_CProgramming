#include "Cards.h"
#include <string>
#include <iostream>

Cards::Cards(string t){
    type = "default";
    // Check if the types are according to the preset values
    for(int i = 0; i < 5; i++){
        if(t.compare(cardTypes[i]) == 0)
            type = t;
    }

    if(type.compare("default") == 0)
        cout << "Type invalid so it is set to default" << endl;
    // If the type is not what expected, default value would be assigned
}

Deck::Deck(int deckSize){
    size = deckSize;
}

Hand::Hand(int handSize){
    size = handSize;
}