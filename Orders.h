#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include <iostream>
#include <string>

//Order class
struct Order
{
private:
    std::string type;
    friend std::ostream& operator<<(std::ostream &strm, const Order &order);

public:
    static std::vector<std::string> ordersType;
    Order();
    Order(std::string newType);
    Order(const Order &o);
    Order& operator =(const Order &o);
    bool validate();
    std::string execute();
    std::string getType();

};

//OrderList class
struct OrdersList
{
private:
    std::vector<Order*> Order_List;
    friend std::ostream& operator<<(std::ostream &strm, const OrdersList &olist);

public:
    OrdersList();
    OrdersList(const OrdersList &o);
    OrdersList& operator =(const OrdersList &o);
    ~OrdersList();
    void add(Order o);
    Order getElement(int index);
    void remove(int index);
    void move(int from, int to);
};


//Order subclasses
struct Advance : public Order
{
private:
    friend std::ostream& operator<<(std::ostream &strm, const Advance &advance);
public:
    Advance();
    void validate();
    std::string execute();
};


struct Deploy : public Order
{
private:
    friend std::ostream& operator<<(std::ostream &strm, const Deploy &deploy);
public:
    Deploy();
    void validate();
    std::string execute();
};


struct Bomb : public Order
{
private:
    friend std::ostream& operator<<(std::ostream &strm, const Bomb &bomb);
public:
    Bomb();
    void validate();
    std::string execute();
};


struct Blockade : public Order
{
private:
    friend std::ostream& operator<<(std::ostream &strm, const Blockade &blockade);

public:
    Blockade();
    void validate();
    std::string execute();
};

struct Airlift : public Order
{
private:
    friend std::ostream& operator<<(std::ostream &strm, const Airlift &airlift);

public:
    Airlift();
    void validate();
    std::string execute();
};

struct Negotiate : public Order
{
private:
    friend std::ostream& operator<<(std::ostream &strm, const Negotiate &negotiate);

public:
    Negotiate();
    void validate();
    std::string execute();
};

#endif