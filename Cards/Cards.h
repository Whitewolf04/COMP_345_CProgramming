#include <string>
using namespace std;

class Cards
{
public:
    string type;
    Cards(string type){};
    void play();
};

class Deck
{
private:
    int size;
public:
    Deck(int size){};
    int getDeckSize(){};
    void draw();
};

class Hand
{
private:
    int size;
public:
    Hand(int size){};
    int getHandSize(){};
    void draw();
};
