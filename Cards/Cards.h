#include <string>
using namespace std;

class Cards
{
public:
    string type;
    const string cardTypes[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
    Cards(string t){};
    void play();
};

class Deck
{
private:
    int size;
public:
    Deck(int deckSize){};
    int getDeckSize(){};
    void draw();
};

class Hand
{
private:
    int size;
public:
    Hand(int handSize){};
    int getHandSize(){};
    void draw();
};
