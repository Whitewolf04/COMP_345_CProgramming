
#include"Player.h"
using namespace std;

Player::Player(vector<Territory*>& t, Hand& h, OrdersList& o){
    territories = t;
    hand = h;
    orders = o;
}

Player::Player(const Player& p){
    this->territories = p.territories;
    this->hand = p.hand;
    this->orders = p.orders;
}

vector<Territory*> Player::toDefend() {

/*territories obj1 = new territories();
cout<<"territory to defend"<<;
cin>>terr;
return obj1 = cin>>territory;*/

}

string Player::toAttack(){

/*territories obj1 = new territories ();
cout<<"territory to defend<<end l";
cin>>territory;
return obj1 = cin>>territory;*/

}

void Player::issueOrder(){

/*Order order_obj = new Oredr();
Cout<<"What are my orders"
Cin>>orders(move);
return obj1.move();*/

}



