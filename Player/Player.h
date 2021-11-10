#pragma once
#include <string>
#include <vector>
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
using namespace std;

class Player {
	private:
		int p_num;
        int reinArmy;
        vector<Territory*> territories;
		Hand hand;
		OrdersList orders;
		friend std::ostream& operator<<(ostream& os, const Player&);

	public:
        // List of players in the game (Available for all player objects)
        static vector<Player*> playerList;

		//Constructors
		Player();
        Player(int pNum);
		Player(vector<Territory*>& t, Hand& h, OrdersList& o, int pNum, int reinArmy); //change
		Player(const Player& p);
		~Player();
		
		//Accessors
		vector<Territory*> getTerritories();
		Hand& getCards();
		OrdersList& getOrders();
        int getPlayerNum(){return p_num;};
        int getReinArmy(){return reinArmy;};

        //Mutator
        void addTerritories(Territory *t);      // Add territory to the player's possession
        void addCards(Cards *c);                // Add cards to hand
        void addOrder(Order *o);                // Add order to the orders list
        void addReinArmy(int add);              // Increase the number of Reinforcement Army
        void removeReinArmy(int remove);        // Decrease the number of Reinforcement Army
        void setPlayerNum(int pNum);            // Set player number

        //Methods
        vector<Territory*>* toDefend();
        vector<Territory*>* toAttack();
        void issueOrder();

};		