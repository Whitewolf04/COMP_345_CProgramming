#include "Cards.h"
#include <string>
#include <iostream>

Cards::Cards(string t){
    *type = "default";
    // Check if the types are according to the preset values
    for(int i = 0; i < 5; i++){
        if(t.compare(*cardTypes[i]) == 0)
            *type = t;
    }

    if((*type).compare("default") == 0)
        cout << "Type invalid so it is set to default" << endl;
    // If the type is not what expected, default value would be assigned
}

Cards::Cards(){
    *type = "default";
}

Deck::Deck(int deckSize){
    *size = deckSize;
    Cards deck[deckSize];
    deckPtr = &deck;
}

int Deck::getDeckSize(){
    return *size;
}

void Deck::draw(Cards hand[], int handSize){
    int deckSize = getDeckSize();
    int cardIndex = rand() % deckSize;
}

Hand::Hand(int handSize){
    *size = handSize;
    Cards hand[handSize];
    handPtr = &hand;
}

int Hand::getHandSize(){
    return *size;
}