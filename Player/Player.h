#include <string>
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
using namespace std;

class Player {
	private:
		int p_num;
        vector<Territory*> territories;
		Hand hand;
		OrdersList orders;
		friend std::ostream& operator<<(ostream& os, const Player&);

	public:
		//Constructors
		Player();
		Player(vector<Territory*>& t, Hand& h, OrdersList& o); //change
		Player(const Player& p);
		~Player();
		
		//Accessors
		vector<Territory*> getTerritories();
		Hand& getCards();
		OrdersList& getOrders();

        //Mutator
        void addTerritories(Territory *t);
        void addCards(Cards *c);
        void addOrder(Order *o);

        //Methods
        vector<Territory*>* toDefend();
        vector<Territory*>* toAttack();
        void issueOrder();

};		