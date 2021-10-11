#include "Cards.cpp"

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

    cout << deck << endl;

    // Drawing cards onto the hand
    hand.drawCard(&deck);
    hand.drawCard(&deck);

    // Print out deck and hand content
    cout << "Hand: \n" << hand << endl;
    cout << "Deck: \n" << deck << endl;

    // Play all the cards on hand
    hand.playCard(0, &deck);
    hand.playCard(0, &deck);

    cout << "\n" << endl;
    cout << "Hand: \n" << hand << endl;
    cout << "Deck: \n" << deck << endl;

    return 0;
}