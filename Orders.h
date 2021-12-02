#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include <iostream>
#include "Map.h"
#include "LoggingObserver.h"
#include "Cards.h"

//Order class
struct Order: Iloggable, Subject
{
private:
    int executor_id;
    int army_count = 0;
    std::string type;
    friend std::ostream& operator<<(std::ostream &strm, const Order &order);

public:
    Order();
    Order(std::string newType);
    Order(std::string newType, int executor_id);
    Order(std::string newType, int executor_id, int army_count);
    Order(const Order &o);
    Order& operator =(const Order &o);
    virtual bool validate() = 0;
    virtual std::string execute()= 0;
    std::string getType();
    int getArmyCount();
    int getExecId();
    Hand* getPlayerHand();
    void stringToLog();

};

//OrderList class
struct OrdersList: Iloggable, Subject
{
private:
    std::vector<Order*> Order_List;
    friend std::ostream& operator<<(std::ostream &strm, const OrdersList &olist);

public:
    OrdersList();
    OrdersList(const OrdersList &o);
    //OrdersList& operator =(const OrdersList &o);
    ~OrdersList();
    void add(Order* o);
    Order* getElement(int index);
    int getSize();
    void remove(int index);
    void move(int from, int to);
    void stringToLog();
};


//Order subclasses
struct Advance : public Order
{
private:
    Territory* source;
    Territory* adjacent;
    bool success = false;
    friend std::ostream& operator<<(std::ostream &strm, const Advance &advance);
public:
    Advance();
    Advance(Territory* source, Territory* adjacent, int executor_id);
    bool validate();
    Territory* getSourceT();
    Territory* getAdjacentT();
    std::string execute();
};


struct Deploy : public Order
{
private:
    Territory* target;
    friend std::ostream& operator<<(std::ostream &strm, const Deploy &deploy);

public:
    Deploy();
    Deploy(int army_count, Territory* target, int executor_id);
    bool validate();
    std::string execute();
};


struct Bomb : public Order
{
private:
    Territory* source;
    Territory* adjacent;
    friend std::ostream& operator<<(std::ostream &strm, const Bomb &bomb);
public:
    Bomb();
    Bomb(Territory* source, Territory* adjacent, int executor_id);
    bool validate();
    std::string execute();
};


struct Blockade : public Order
{
private:
    Territory* target;
    friend std::ostream& operator<<(std::ostream &strm, const Blockade &blockade);

public:
    Blockade();
    Blockade(Territory* target, int executor_id);
    bool validate();
    Territory* getTarget();
    std::string execute();
};

struct Airlift : public Order
{
private:
    Territory* source;
    Territory* target;
    friend std::ostream& operator<<(std::ostream &strm, const Airlift &airlift);

public:
    Airlift();
    Airlift(int army_count, Territory* source, Territory* target, int executor_id);
    bool validate();
    std::string execute();
};

struct Negotiate : public Order
{
private:
    int target_id;
    friend std::ostream& operator<<(std::ostream &strm, const Negotiate &negotiate);

public:
    Negotiate();
    Negotiate(int target_id, int executor_id);
    bool validate();
    int getTargetId();
    std::string execute();
};

#endif