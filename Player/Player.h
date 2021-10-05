#include <string>
using namespace std;

class Player {
	private:
		int p_num;
        vector<Territory>* territories = new vector<Territory>;
		vector<Cards>* hand = new vector<Cards>;
		vector<Orders>* hand = new vector<Orders>;

	public:
		//Constructors
		Player(Territory t[], Cards hand, Orders o); //change
		Player(const Player& p);
		
		//Accessors
		vector<Territory>& getTerritories();
		vector<Cards>& getCards();
		vector<Orders>& getOrders();

        //Mutator
        void addTerritories(Territory& t);
        void addCards(Cards& c);
        void addOrders(Orders& o);

        //Methods
        string toDefend();
        string toAttack();
        void issueOrder();

}		