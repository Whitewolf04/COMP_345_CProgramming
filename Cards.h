#ifndef CARDS_H
#define CARDS_H
#include "LoggingObserver.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Order;

class Cards
{
private:
    friend std::ostream& operator<<(std::ostream&, const Cards&);
public:
    static vector<string> types;
    string type;
    Cards();
    Cards(string t);
    Cards(const Cards* other);
    bool equals(const Cards *other);
    bool equals(string cardType);
    Order* play();
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
    Order * playCard(string cardType);
    bool contains(string cardType);
};

#endif