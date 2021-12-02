#pragma once

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
};

class Human : PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

class Neutral : PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

class Aggressive : PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

class Benevolent : PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

class Cheater : PlayerStrategy{

    public:
    void issueOrder(Order* o);
    void toAttack();
    void toDefend();

};

