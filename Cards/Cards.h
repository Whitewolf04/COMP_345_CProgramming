#include <string>
using namespace std;

class Cards
{
private:
    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
public:
    string type;
    Cards(){};
    Cards(string t){};
    bool equals(Cards *other);
    void play(Deck *deck);
};

class Deck
{
private:
    int size;
    int deckIndex;
    Cards *deck = new Cards[size];
public:
    Deck(int deckSize){};
    int getDeckSize(){};
    void add(Cards *newCard);
    void remove(Cards *target);
    void draw(Hand *hand);
};

class Hand
{
private:
    int size;
    int handIndex;
    Cards *hand = new Cards[size];
public:
    Hand(int handSize){};
    int getHandSize(){};
    void add(Cards *newCard);
    void remove(Cards *target);
    void playCard(int index, Deck *deck);
};
