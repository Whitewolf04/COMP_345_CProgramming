#include <string>
using namespace std;

class Cards
{
private:
    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
    string *cardTypes = types;
public:
    string* type = new string();
    Cards(){};
    Cards(string t){};
    bool equals(Cards other);
    void play();
};

class Deck
{
private:
    int* size = new int();
    Cards *deckPtr;
public:
    Deck(int deckSize){};
    int getDeckSize(){};
    void add(Cards newCard);
    void remove(Cards target);
    void draw(Cards hand[], int handSize);
};

class Hand
{
private:
    int* size = new int();
    int* handIndex = new int();
    Cards *handPtr;
public:
    Hand(int handSize){};
    int getHandSize(){};
    void add(Cards newCard);
    void remove(Cards target);
};
