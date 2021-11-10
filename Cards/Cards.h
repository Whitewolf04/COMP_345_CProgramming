#pragma once
#include <string>
#include <vector>
using namespace std;

class Cards
{
private:
    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
    friend std::ostream& operator<<(std::ostream&, const Cards&);
public:
    string type;
    Cards();
    Cards(string t);
    bool equals(Cards *other);
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
    Cards* draw();
};

class Hand
{
private:
    int size;
    std::vector<Cards*> hand;
    friend std::ostream& operator<<(std::ostream&, const Hand&);
public:
    Hand();
    Hand(int handSize);
    ~Hand();
    int getHandSize();
    void add(Cards *newCard);
    void remove(Cards *target);
    void drawCard(Deck *deck);
    void playCard(int index, Deck *deck);
};

