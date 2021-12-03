#pragma once

#include <string>
using std::string;

class Player;
class Order;

class PlayerStrategy{
    private:
    Player* p;
    public:
    virtual void issueOrder(Order* o)=0;
    virtual void toAttack()=0;
    virtual void toDefend()=0;
    Player* getPlayer();
    void setPlayer(Player* pl);
};

class Human : public PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();


};

class Neutral : public PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

class Aggressive : public PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

class Benevolent : public PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

class Cheater : public PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

