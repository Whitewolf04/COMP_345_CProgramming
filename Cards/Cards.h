#include <string>
using namespace std;

class Cards
{
public:
    string* type = new string();
    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
    string (*cardTypes)[5] = &types;
    Cards(string t){};
    void play();
};

class Deck
{
private:
    int* size = new int();
public:
    Deck(int deckSize){};
    int getDeckSize(){};
    void draw();
};

class Hand
{
private:
    int* size = new int();
public:
    Hand(int handSize){};
    int getHandSize(){};
    void draw();
};
