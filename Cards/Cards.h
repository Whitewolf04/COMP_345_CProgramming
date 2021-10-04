#include <string>
using namespace std;

class Cards
{
public:
    string* type = new string();
    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
    string (*cardTypes)[5] = &types;
    Cards(){};
    Cards(string t){};
    void play();
};

class Deck
{
private:
    int* size = new int();
    Cards (*deckPtr)[];
public:
    Deck(int deckSize){};
    int getDeckSize(){};
    void draw(Cards hand[], int handSize);
};

class Hand
{
private:
    int* size = new int();
    Cards (*handPtr)[];
public:
    Hand(int handSize){};
    int getHandSize(){};
};
