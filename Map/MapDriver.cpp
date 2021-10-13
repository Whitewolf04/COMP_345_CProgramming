#include "Map.h"
using namespace std;

int main() {

	Player p1(4);
	Map map1;
	map1.validate();
	Map map2(map1);
	Map map3;

	map2.printNodeList();
	cout << map3.getNode(3)->getPlayerNumber() << endl;

	map3.getNode(3)->setPlayerNumber(p1.getPlayerNum());
	cout << map3.getNode(3)->getPlayerNumber() << endl;
	return 0;
}