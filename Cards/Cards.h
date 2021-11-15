#ifndef CARDS_H
#define CARDS_H
#include "LoggingObserver.h"
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

//enum CardTypes {defaultType, bomb, reinforcement, blockade, airlift, diplomacy};

class Cards
{
private:
    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
    friend std::ostream& operator<<(std::ostream&, const Cards&);
public:
    string type;
    Cards();
    Cards(string t);
    Cards(const Cards* other);
    bool equals(const Cards *other);
    bool equals(string cardType);
    void play();
};

class Deck
{
private:
    int size;
    std::vector<Cards*> deck;
    friend std::ostream& operator<<(std::ostream&, const Deck&);
public:
    Deck(int deckSize);
    ~Deck();
    int getDeckSize();
    void add(Cards *newCard);
    void remove(Cards *target);
    Cards draw();
};

class Hand
{
private:
    int size;
    std::vector<Cards*> hand;
    friend std::ostream& operator<<(std::ostream&, const Hand&);
public:
    // Constructor and Destructor
    Hand();
    Hand(int handSize);
    ~Hand();

    // Accessor
    int getHandSize();

    // Mutator
    void add(Cards* newCard);
    void remove(Cards *target);

    // Operational methods
    void drawCard(Deck *deck);
    void playCard(string cardType);
    bool contains(string cardType);
};

#endif