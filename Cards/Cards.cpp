#include "Cards.h"
#include <string>
#include <iostream>

Cards::Cards(string t){
    type = "default";
    // Check if the types are according to the preset values
    for(int i = 0; i < 5; i++){
        if(t.compare(types[i]) == 0)
            type = t;
    }

    if(type.compare("default") == 0)
        cout << "Type invalid so it is set to default" << endl;
    // If the type is not what expected, default value would be assigned
}

Cards::Cards(){
    type = "default";
}

bool Cards::equals(Cards *other){
    if((this->type).compare((*other).type) == 0){
        return true;
    }
    return false;
}

void Cards::play(Deck *deck){
    // Add this card to the list of orders
    cout << "Card has been added to the list of orders" << endl;

    // Return the card to the deck
    (*deck).add(this);
}

Deck::Deck(int deckSize){
    size = deckSize;
    deckIndex = 0;
}

int Deck::getDeckSize(){
    return size;
}

void Deck::draw(Hand *hand){
    int deckSize = getDeckSize();
    int cardIndex = rand() % deckSize;
    Cards drawn = deck[cardIndex];

    // Add the new card to the player's hand
    (*hand).add(&drawn);

    // Remove the card drawn from the deck
    remove(&drawn);
}

void Deck::add(Cards *card){
    deck[deckIndex] = *card;
    deckIndex++;
}

void Deck::remove(Cards *target){
    int removeIndex = -1;

    // Loop through the hand to find the target card
    for(int i = 0; i < size; i++){
        Cards temp = deck[i];
        if((*target).equals(&temp)){
            removeIndex = i;
            break;
        }
    }

    // Check if the target was found
    if(removeIndex == -1){
        return;
    }

    for(int i = removeIndex; i < (size-1); i++){
        deck[i] = deck[i+1];
    }
    // Setting the last item to be Null if it is not Null yet
    Cards *tempPtr = &deck[size-1];
    tempPtr = NULL;

    // Decrement the deckIndex
    deckIndex--;
}

Hand::Hand(int handSize){
    size = handSize;
    handIndex = 0;
}

int Hand::getHandSize(){
    return size;
}

void Hand::add(Cards *newCard){
    hand[handIndex] = *newCard; 
    handIndex++;
}

void Hand::remove(Cards *target){
    int removeIndex = -1;

    // Loop through the hand to find the target card
    for(int i = 0; i < size; i++){
        Cards temp = hand[i];
        if((*target).equals(&temp)){
            removeIndex = i;
            break;
        }
    }

    // Check if the target was found
    if(removeIndex == -1){
        return;
    }

    for(int i = removeIndex; i < (size-1); i++){
        hand[i] = hand[i+1];
    }
    // Setting the last item to be Null if it is not Null yet
    Cards *tempPtr = &hand[size-1];
    tempPtr = NULL;

    // Decrement the handIndex
    handIndex--;
}

void Hand::playCard(int index, Deck *deck){
    hand[index].play(deck);
}