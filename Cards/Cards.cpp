#include "Cards.h"
#include <string>
#include <iostream>

// Cards default constructor
Cards::Cards(){
    type = "default";
}

// Cards constructor initializing with a card type
Cards::Cards(string t){
    type = "default";
    // Check if the types are according to the preset values
    for(int i = 0; i < 5; i++){
        if(t.compare(types[i]) == 0)
            type = t;
    }

    // If the type is not what expected, default value would be assigned
    if(type.compare("default") == 0)
        cout << "Type invalid so it is set to default" << endl;
}

Cards::Cards(Cards* anotherCard){
    this->type = anotherCard->type;
}

// Comparing two cards to see if they are off the same type
bool Cards::equals(Cards* other){
    if(this->type == other->type){
        return true;
    }
    return false;
}

// Comparing the current card with a card name string
bool Cards::equals(string cardType){
    if(this->type == cardType){
        return true;
    }
    return false;
}

// Play method adding the card to list of orders
void Cards::play(){
    // Add this card to the list of orders
    cout << "Card " << this->type << " has been added to the list of orders" << endl;
}

// Show the card type
std::ostream& operator<<(std::ostream &strm, const Cards &card){
    return strm << card.type;
}

// Constructor initializing a deck with deck size
Deck::Deck(int deckSize){
    size = deckSize;
}

// Destructor to delete all the pointers on deck vector
Deck::~Deck(){
     for(int i = 0; i < deck.size(); i++){
         free(deck[i]);
         deck[i] = nullptr;
     }
}

// Deck size getter
int Deck::getDeckSize(){
    return size;
}

// Draw a card from the deck
Cards* Deck::draw(){
    int deckSize = getDeckSize();
    int cardIndex = rand() % deckSize;
    Cards* drawn = deck[cardIndex];

    // Remove the card drawn from the deck
    // Temporarily disable removing from deck
//    remove(drawn);

    // Return the drawn card
    return drawn;
}

// Add a card to the deck
void Deck::add(Cards *card){
    deck.push_back(card);
}

// Remove a specific card from the deck
void Deck::remove(Cards *target){
    int removeIndex = -1;

    // Loop through the hand to find the target card
    for(int i = 0; i < deck.size(); i++){
        Cards * temp = deck.at(i);
        if(target->equals(temp)){
            removeIndex = i;
            break;
        }

        // Testing
        // delete temp;
    }

    // Check if the target was found
    if(removeIndex == -1){
        return;
    }

    // Remove the target from the vector
    deck.erase(deck.begin()+removeIndex);
}

// Show all the cards on deck
std::ostream& operator<<(std::ostream &stream, const Deck &obj){
    string output = "";
    for(int i = 0; i < obj.deck.size(); i++){
        Cards temp = *(obj.deck.at(i));
        output += temp.type;
        output += " card\n";
    }

    return stream << output;
}

// Default constructor for Hand
Hand::Hand(){
    size = 0;
}

// Constructor initializing hand with hand size
Hand::Hand(int handSize){
    size = handSize;
}

// Destructor deleting all the pointers in hand vector
Hand::~Hand(){
     for(int i = 0; i < hand.size(); i++){
         free(hand[i]);
         hand[i] = nullptr;
     }
}

// Hand size getter
int Hand::getHandSize(){
    return size;
}

// Add a new card to the hand
void Hand::add(Cards *newCard){
    hand.push_back(newCard);
}

// Remove a specific card from the hand
void Hand::remove(Cards *target){
    int removeIndex = -1;

    // Loop through the hand to find the target card
    for(int i = 0; i < hand.size(); i++){
        Cards *temp = hand.at(i);
        if((*target).equals(temp)){
            removeIndex = i;
            break;
        }

        // Testing 
        // delete temp;
    }

    // Check if the target was found
    if(removeIndex == -1){
        return;
    }

    // Remove the target from hand
    hand.erase(hand.begin()+removeIndex);
}

// Draw a card from deck to hand
void Hand::drawCard(Deck *deck){
    Cards *drawn = (*deck).draw();
    this->add(drawn);
}

// Play a card at a certain position on hand
// Assume that the card can definitely be found on hand
void Hand::playCard(string cardType){
    Cards *temp;

    for(int i = 0; i < hand.size(); i++){
        temp = hand.at(i);
        if(temp->equals(cardType)){
            break;
        }
    }
    temp->play();

    // Remove the card that was played from hand, and add it back to the deck
    remove(temp);
//    deck->add(temp);
}

// Check if hand contains a certain card
bool Hand::contains(string cardType){
    bool found = false;

    for(int i = 0; i < hand.size(); i++){
        Cards* temp = hand.at(i);
        if(temp->equals(cardType)){
            found = true;
            break;
        }
    }

    return found;
}

// Show all the current cards on hand
std::ostream& operator<<(std::ostream &stream, const Hand &obj){
    string output = "";
    for(int i = 0; i < obj.hand.size(); i++){
        Cards temp = *(obj.hand.at(i));
        output += temp.type;
        output += " card\n";
    }

    return stream << output;
}