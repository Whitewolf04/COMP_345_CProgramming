#include <vector>
#include <iostream>

struct Order
{
    private:
    const std::string name = "Order";
    friend std::ostream& operator<<(std::ostream &strm, const Order &order);

    public:
    void validate();
    void execute();
    std::string getName();
    
};

struct OrdersList
{
    private:
    
    friend std::ostream& operator<<(std::ostream &strm, const OrdersList &olist);

    public:
    std::vector<Order*> Order_List;
    OrdersList();
    OrdersList(const OrdersList &o);
    OrdersList& operator =(const OrdersList &o);
    void add(Order o);
    Order getElement(int index);
    void remove(int index);
    void move();
};



struct Advance : public Order
{
    /* data */
    private:
    const std::string name = "Advance";

    public:
    void validate();
    void execute();
};


struct Deploy : public Order
{
    /* data */
    public:
    void validate();
    void execute();
};


struct Bomb : public Order
{
    /* data */

    public:
    void validate();
    void execute();
};


struct Blockade : public Order
{
    /* data */

    public:
    void validate();
    void execute();
};

struct Airlift : public Order
{
    /* data */

    public:
    void validate();
    void execute();
};

struct Negotiate : public Order
{
    /* data */

    public:
    void validate();
    void execute();
};