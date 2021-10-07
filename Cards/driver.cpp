#include <iostream>
#include "Cards.cpp"\

int main(){
    // Initialize all the cards
    Cards bomb = Cards("bomb");
    Cards reinforcement = Cards("reinforcement");
    Cards blockade = Cards("blockade");
    Cards airlift = Cards("airlift");
    Cards diplomacy = Cards("diplomacy");

    Deck deck = Deck(5);
    Hand hand = Hand(2);

    // Adding cards to the Deck
    deck.add(&bomb);
    deck.add(&reinforcement);
    deck.add(&blockade);
    deck.add(&airlift);
    deck.add(&diplomacy);

    deck.draw(&hand);
    deck.draw(&hand);

    // Play all the cards on hand
    hand.playCard(0, &deck);
    hand.playCard(1, &deck);

    return 0;
}