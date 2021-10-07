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

bool Cards::equals(Cards *other){
    if((this->type).compare((*other).type) == 0){
        return true;
    }
    return false;
}

void Cards::play(){
    // Add this card to the list of orders
    cout << "Card " << this->type << " has been added to the list of orders" << endl;
}

std::ostream& operator<<(std::ostream &strm, const Cards &card){
    return strm << card.type;
}

Deck::Deck(int deckSize){
    size = deckSize;
}

int Deck::getDeckSize(){
    return size;
}

Cards Deck::draw(){
    int deckSize = getDeckSize();
    int cardIndex = rand() % deckSize;
    Cards drawn = deck[cardIndex];

    // Add the new card to the player's hand

    // Remove the card drawn from the deck
    remove(&drawn);

    // Return the drawn card
    return drawn;
}

void Deck::add(Cards *card){
    deck.push_back(*card);
}

void Deck::remove(Cards *target){
    int removeIndex = -1;

    // Loop through the hand to find the target card
    for(int i = 0; i < deck.size(); i++){
        Cards temp = deck.at(i);
        if((*target).equals(&temp)){
            removeIndex = i;
            break;
        }
    }

    // Check if the target was found
    if(removeIndex == -1){
        return;
    }

    // Remove the target from the vector
    deck.erase(deck.begin()+removeIndex);
}

std::ostream& operator<<(std::ostream &stream, const Deck &obj){
    string output = "";
    for(int i = 0; i < obj.deck.size(); i++){
        output += obj.deck.at(i).type;
        output += " card\n";
    }

    return stream << output;
}

Hand::Hand(int handSize){
    size = handSize;
}

int Hand::getHandSize(){
    return size;
}

void Hand::add(Cards *newCard){
    hand.push_back(*newCard);
}

void Hand::remove(Cards *target){
    int removeIndex = -1;

    // Loop through the hand to find the target card
    for(int i = 0; i < hand.size(); i++){
        Cards temp = hand.at(i);
        if((*target).equals(&temp)){
            removeIndex = i;
            break;
        }
    }

    // Check if the target was found
    if(removeIndex == -1){
        return;
    }

    // Remove the target from hand
    hand.erase(hand.begin()+removeIndex);
}

void Hand::playCard(int index, Deck *deck){
    Cards temp = hand.at(index);
    temp.play();

    // Remove the card that was played from hand, and add it back to the deck
    remove(&temp);
    (*deck).add(&temp);
}

std::ostream& operator<<(std::ostream &stream, const Hand &obj){
    string output = "";
    for(int i = 0; i < obj.hand.size(); i++){
        output += obj.hand.at(i).type;
        output += " card\n";
    }
    
    return stream << output;
}