#include <string>
#include "Cards/Cards.cpp"
#include "Orders/Orders.cpp"
#include "Map/Map.cpp"
using namespace std;

class Player {
	private:
		int p_num;
        vector<Territory*> territories;
		Hand hand;
		OrdersList orders;

	public:
		//Constructors
		Player(vector<Territory*>& t, Hand& h, OrdersList& o); //change
		Player(const Player& p);
		
		//Accessors
		vector<Territory*> getTerritories();
		Hand& getCards();
		OrdersList& getOrders();

        //Mutator
        void addTerritories(Territory& t);
        void addCards(Cards& c);
        void addOrders(OrdersList& o);

        //Methods
        vector<Territory*> toDefend();
        string toAttack();
        void issueOrder();

};		