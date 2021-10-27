#include "Map.h"

using namespace std;

string MapLoader::FileLoader(ifstream *stream)
{
	string *Mapname = new string();
	ifstream *fs = stream;
	cout << "Enter the name of the map you wish to use." << endl;
	cin >> *Mapname;
	cout << "Opening " << *Mapname << " file for Parsing...." << endl;

	fs->open(*Mapname);
	if (*fs)
	{
		cout << "file exists\nProceeding with the file parsing\n";
	}
	else
	{
		cout << "file doesn't exist\n";
	}
	delete Mapname;
	return string((std::istreambuf_iterator<char>(*fs)), std::istreambuf_iterator<char>());
}
bool MapLoader::FileParser(string &str, vector<Continent> &c, vector<Territory> &t)
{

	//Making pointers to passed varaibles
	string *file = &str;
	vector<Continent> *C = &c;
	vector<Territory> *T = &t;
	//Making variables that will be used to read from the input string
	istringstream stream(*file);
	string *line = new string();
	//Initializing local scope variables
	int order = 0;
	int ContinentOrder = 1;
	int TerritoryOrder = 1;
	int NodeNumber = 0;
	bool valid = true;
	bool ContinentMark = false;
	bool TerritoryMark = false;
	bool BorderMark = false;

	while (getline(stream, *line))
	{
		//If the file is marked as invalid anywhere down below, it will empty the values of Continent and Territory passed vectors
		//The reason they are emptied is to make it possible for them to be re-used if needed.
		if (!valid)
		{
			cout << "Invalid file... Discarting Input Map\n";
			cout << "Emptying Continent List\n";
			C->clear();
			cout << "Emptying Territory List\n";
			T->clear();
			break;
		}
		//Following section basically checks if the file format for the maps is the correct one
		if (*line == "[continents]")
		{
			order = 1;
			continue;
		}
		else if (*line == "[countries]" && ContinentMark)
		{
			// After the continents section is checked, the Territories section will be checked
			// For the Territories to be checked in the first place, the Continent section needs to have been valid
			order = 2;
			continue;
		}
		else if (*line == "[countries]" && !ContinentMark)
		{
			cout << "The file is missing a section...\n";
			valid = false;
			continue;
		}
		else if (*line == "[borders]" && TerritoryMark && ContinentMark)
		{
			order = 3;
			continue;
		}
		else if (*line == "[borders]" && (!ContinentMark || !TerritoryMark))
		{
			cout << "The file is missing a section...\n";
			valid = false;
			continue;
		}

		if (order == 1 && *line != "")
		{

			//Extrapolating the Information from the File for Use
			string *NameOfContinent = new string();
			string *NumberOfArmies = new string();
			string *Colour = new string();
			int IntegerAmountOfArmies;
			try
			{
				IntegerAmountOfArmies = Continent::Parsing(*line, *NameOfContinent, *NumberOfArmies, *Colour);
			} //Accepts floats, 2 fix l8r, if colour missing, still works
			catch (exception e)
			{
				cout << "Parsing error at Continent Section, Invalid format..\n";
				valid = false;
				continue;
			}

			//Adding a Continent Object with the Above Values to the passed Vector of Continents
			Continent c(ContinentOrder, *NameOfContinent, IntegerAmountOfArmies, *Colour);
			addContinents(c, C);
			ContinentOrder++;

			//Avoiding MLeak
			delete NameOfContinent, NumberOfArmies, Colour;
		}
		else if (order == 1 && *line == "")
		{
			ContinentMark = true; //Continent section has been fully parsed
			order = 0;
		}
		else if (order == 2 && *line != "")
		{

			//Extrapolating the Information from the File for Use
			string *NameOfTerritory = new string();
			string *ContinentNumberofTerritory = new string();
			int IntegerNumberOfContinent;
			try
			{
				IntegerNumberOfContinent = Territory::Parsing(*line, *NameOfTerritory, *ContinentNumberofTerritory);
			}
			catch (exception e)
			{
				cout << "Parsing error at Territory Section, Invalid format..\n";
				valid = false;
				continue;
			}

			//Accessing the amount of armies that each continent has for its armies
			int numOfArmies = 0;
			try
			{
				numOfArmies = C->at(IntegerNumberOfContinent - 1).getCCB();
			}
			catch (exception e)
			{
				cout << "Problem with accessing a certain continent number to add armies.\n";
				valid = false;
				break;
			}

			//Adding a Territory Object with the Above Values to the passed Vector of Territories
			Territory t(TerritoryOrder, numOfArmies, *NameOfTerritory, IntegerNumberOfContinent);
			MapLoader::addTerritory(t, T);
			TerritoryOrder++;

			//Avoiding MLeak
			delete NameOfTerritory, ContinentNumberofTerritory, t;
		}
		else if (order == 2 && *line == "")
		{
			TerritoryMark = true; //Territory section has been fully parsed
			order = 0;
		}
		else if (order == 3 && *line != "")
		{

			BorderMark = true;
			//Parsing the file for the Values of Each Border
			stringstream ss(*line);
			string word;			// Needed to read each line
			vector<int> Connexions; // Temporarly stores all connexions of a specific node
			int i = 0;
			int j = 0;

			while (ss >> word)
			{
				//Avoids the first value (It's the node number representing each Territory)
				if (j == 0)
				{
					j++;
					continue;
				}

				//Adds the neighboring nodes to the Connexions vector defined above
				try
				{
					Connexions.push_back(stoi(word));
				} //Try catch used to avoid non-integer values added
				catch (exception e)
				{
					cout << "Parsing error at Border Section, Invalid format..\n";
					valid = false;
					break;
				}
			}
			if (valid)
			{
				for (int i = 0; i < Connexions.size(); i++)
				{
					//Adds the value of the Connexions vector defined above to the corresponding node (NodeNumber)
					//For the Node 1, it will add whatever has been identified in the while loop and added to Connexions
					//For the Node 2, it will do the same for that line, etc..
					T->at(NodeNumber).addNeighbors(Connexions.at(i));
				}
			}
			NodeNumber++;
		}
	}

	delete line;
	if ((!ContinentMark || !TerritoryMark || !BorderMark) && valid)
	{ //checks if all sections have been identified, if not cancels the map loading
		cout << "Invalid file... Discarting Input Map\n";
		cout << "Emptying Continent List\n";
		C->clear();
		cout << "Emptying Territory List\n";
		T->clear();
	};
	return valid;
}

//Definiton of Methods to add Continents and Territories to the passed vectors (Arguments : C/T object and C/T Vectors)
void MapLoader::addContinents(Continent c, vector<Continent> *v)
{
	v->push_back(c);
}
void MapLoader::addTerritory(Territory t, vector<Territory> *v)
{
	v->push_back(t);
}

//Constructor//AssignmentOperator Definitions
Territory::Territory(){

};
Territory::Territory(int i, int i2, string s, int i3)
{
	T_num = i;
	NumOfArmies = i2;
	T_name = s;
	Continent_Number = i3;
}
Territory::Territory(const Territory &t)
{
	T_num = t.T_num;
	NumOfArmies = t.NumOfArmies;
	T_name = t.T_name;
	Continent_Number = t.Continent_Number;
	NeighboringTerritories = t.NeighboringTerritories;
}
Territory &Territory::operator=(const Territory &t)
{
	return *this;
}

Continent::Continent(int i, string s, int i2, string s2)
{
	C_num = i;
	C_name = s;
	CCBus = i2;
	colour = s2;
}
Continent::Continent(const Continent &c)
{
	C_num = c.C_num;
	C_name = c.C_name;
	CCBus = c.CCBus;
	colour = c.colour;
}
Continent &Continent::operator=(const Continent &t) { return *this; }

//Map Constructor
Map::Map()
{

	ifstream *stream = new ifstream();
	string *MapInformation = new string();
	vector<Continent> *Continents = new vector<Continent>;
	vector<Territory> *Territories = new vector<Territory>;
	bool works = false;
	*MapInformation = MapLoader::FileLoader(stream);
	works = MapLoader::FileParser(*MapInformation, *Continents, *Territories);
	if (!works)
	{
		cout << "The map is not valid, map object will be emptied.\n";
	}
	else
	{
		for (int i = 0; i < Territories->size(); i++)
		{
			ListOfNodes->push_back(Territories->at(i));
		}
		for (int i = 0; i < Continents->size(); i++)
		{
			ListOfContinents->push_back(Continents->at(i));
		}

		for (int i = 0; i < ListOfNodes->size(); i++)
		{
			vector<int> x = Territories->at(i).getTerritoryConnexions();
			for (int j = 0; j < x.size(); j++)
			{
				try
				{
					ListOfNodes->at(i).addEdges(&ListOfNodes->at(x.at(j) - 1));
				}
				catch (exception e)
				{
				}
			}
		}
	}
	delete Territories, Continents, stream, MapInformation;
}
Map::Map(const Map &m)
{
	*ListOfNodes = *m.ListOfNodes;
	*ListOfContinents = *m.ListOfContinents;
}

//Map methods
void Map::printNodeList()
{
	for (int i = 0; i < ListOfNodes->size(); i++)
	{
		cout << ListOfNodes->at(i) << endl;
	}
};
void Map::printContinentList()
{
	for (int i = 0; i < ListOfContinents->size(); i++)
	{
		cout << "For Continent " << i << " : " << &ListOfContinents->at(i) << endl;
		cout << ListOfContinents->at(i) << endl;
		cout << "------------------" << endl;
	}
};
bool Map::advance(int n, int m)
{
	//Used to see if a node is connected to another
	bool possible = false;
	for (int i = 0; i < ListOfNodes->at(n - 1).getEdges().size(); i++)
	{
		if (ListOfNodes->at(n - 1).getEdges().at(i) == &ListOfNodes->at(m - 1))
		{
			possible = true;
		}
	}
	if (!possible)
	{
		//cout << "Movement from " << n << " to " << m << " is not possible" << endl;
	}
	return possible;
}
bool Map::PlayerCheck(int node, int playerN)
{
	//Used to check if a territory belongs to a certain playerN
	return (ListOfNodes->at(node).getPlayerNumber() == playerN ? true : false);
};
bool Map::validate()
{
	bool TerritoriesConnected = false;
	bool ContinentsConnected = false;
	bool TerritoryhasOneContinent = false;
	vector<int> destination;

	//For territory-country check
	vector<string> names;
	bool twice = false;
	//Checks if a node is added two times to the list of nodes, this way, a node cannot have two continents AND there cannot be two same
	//nodes in the same map
	for (int i = 0; i < ListOfNodes->size(); i++)
	{
		if (find(names.begin(), names.end(), ListOfNodes->at(i).getTerritoryName()) == names.end())
		{
			names.push_back(ListOfNodes->at(i).getTerritoryName());
		}
		else
		{
			cout << "An element exists twice.\n";
			twice = true;
			break;
		}
	}

	if (!twice)
	{
		TerritoryhasOneContinent = true;
	}
	if (TerritoryhasOneContinent)
	{
		cout << "Each territory belongs to one Continent\n";
	}
	else
	{
		cout << "a territory belongs to more than one Continent\n";
	}
	if (TerritoryhasOneContinent)
	{
		//For Continent Subgraph Check
		{
			//This section will add to an array each node of each continent and try to find a permutation where it
			//one node can advance to the next one and then try to do the same for the inverse of that permutation
			//This way a continent will 100% be connected and be reachable from any node within it
			cout << "Checking if the continents are connected subgraphs..." << endl;
			for (int c = 1; c <= ListOfContinents->size(); c++)
			{
				cout << "CHECKING FOR CONTINENT NUMBER " << c << ". ---------------------------------------------\n";
				vector<int> checkpoints;
				vector<int> marks;
				int starter = 0;
				bool connectedForward = false;
				bool connectedBackwards = false;
				for (int j = 0; j < getNodesForContinent(c).size(); j++)
				{
					if (j == 0 && getNodesForContinent(c).size() != 1)
					{
						starter = getNodesForContinent(c).at(j).getTerritoryNumber();
					}
					checkpoints.push_back(getNodesForContinent(c).at(j).getTerritoryNumber());
				}
				if (checkpoints.size() == 1)
				{
					cout << "Continent contains a single node, no need to check.\n";
					continue;
				}
				do
				{

					marks = checkpoints;
					if (marks.size() != 1 && starter == marks.at(0))
					{

						//Loop to check if the a path exists
						for (int i = 0; i < marks.size() - 1; i++)
						{

							if (!advance(marks.at(i), marks.at(i + 1)))
							{
								connectedForward = false;
								break;
							}
							else if (advance(marks.at(i), marks.at(i + 1)) && i == marks.size() - 2)
							{
								cout << "Checking the following path: ";
								for (int i = 0; i < marks.size(); i++)
								{
									cout << marks.at(i) << " ";
								}
								cout << endl;
								cout << "Forward Path works for this continent\nNow checking if it works the other way around:";
								connectedForward = true;
							};
						}
						if (connectedForward)
						{
							//Checking the backwards path
							reverse(marks.begin(), marks.end());
							for (int i = 0; i < marks.size(); i++)
							{
								cout << marks.at(i) << " ";
							}
							cout << endl;
							for (int i = 0; i < marks.size() - 1; i++)
							{

								if (!advance(marks.at(i), marks.at(i + 1)))
								{
									break;
								}
								else if (advance(marks.at(i), marks.at(i + 1)) && i == marks.size() - 2)
								{
									cout << "Path works for this continent\n";
									connectedBackwards = true;
								};
							}
							if (connectedBackwards)
							{
								cout << "Also connected backwards, path is valid and continent.\n";
							}
						}
					}
					else
					{
						break;
					} //If They are connected, we break and go check the next continent
					if (connectedForward && connectedBackwards)
					{
						cout << "Continent Number " << c << " is connected\n";
						ContinentsConnected = true;
						break;
					}
					else
					{
						ContinentsConnected = false;
					}
				} while (next_permutation(checkpoints.begin(), checkpoints.end()));
				if (!ContinentsConnected)
				{
					break;
				}
				cout << "FINISHED CHECKING---------------------------------------\n\n";
			}
		}
		if (ContinentsConnected)
		{
			cout << "Continents are a connected subraph\n";
		}
		else
		{
			cout << "Continents are not a connected subraph\n";
		}
		if (ContinentsConnected)
		{

			cout << "\n\n\nChecking if the entire graph is connected and accessible...\n";
			vector<vector<int> > Cnodes; //Vector of a vector of nodes that contain all the nodes of a specific continent
			for (int i = 0; i < ListOfContinents->size(); i++)
			{
				vector<int> add;
				for (auto j : getNodesForContinent(i + 1))
				{
					add.push_back(j.getTerritoryNumber());
				}
				Cnodes.push_back(add);
			}
			bool exists = false;
			//We check if every continent has a node that can be accessed from outside the continent
			//We will later check if every continent leads to the outside
			//Uses a vector of vector<int> called C(ontinent)nodes. If any node of this continent is a neighbor of a node
			//that is isnt part of this continent, then it is possible to access this continent
			for (int i = 0; i < Cnodes.size(); i++)
			{
				exists = false;
				for (int j = 0; j < Cnodes.at(i).size(); j++)
				{

					for (int k = 0; k < ListOfNodes->size(); k++)
					{

						if (ListOfNodes->at(k).getTerritoryContinent() != i + 1)
						{
							for (auto l : ListOfNodes->at(k).getTerritoryConnexions())
							{
								if (l == Cnodes.at(i).at(j))
								{
									destination.push_back(ListOfNodes->at(k).getTerritoryContinent() - 1);
									cout << ListOfContinents->at(i).getContinentName() << " can be accessed from " << ListOfContinents->at(ListOfNodes->at(k).getTerritoryContinent() - 1).getContinentName() << endl;
									exists = true;
									break;
								}
							}
						}
						if (exists)
						{
							break;
						}
					}
				}
				if (!exists)
				{
					break;
				}
			}
			if (!exists)
			{
				cout << "A certain Continent cannot be accessed.\n";
			}
			else
			{
				bool repeat = true;
				//We check if every continent has a node that can be access a continent other than itself
				cout << "\nEach continent can be accessed. Now checking if every continent leads to another one other than itself.\n\n";
				bool canExit = false;
				for (int i = 0; i < Cnodes.size(); i++)
				{
					canExit = false;
					for (int j = 0; j < Cnodes.at(i).size(); j++)
					{ //This loop serves to see where each node connects to
						if (ListOfNodes->at(Cnodes.at(i).at(j) - 1).getTerritoryConnexions().size() == 0)
						{
							break;
						}
						for (auto k : ListOfNodes->at(Cnodes.at(i).at(j) - 1).getTerritoryConnexions())
						{
							if (ListOfNodes->at(k - 1).getTerritoryContinent() - 1 != i)
							{ // This is to check that the node does not connect to itself
								cout << "From Continent " << ListOfContinents->at(i).getContinentName() << ", you can go to " << ListOfContinents->at(ListOfNodes->at(k - 1).getTerritoryContinent() - 1).getContinentName() << endl;
								if (repeat && (getNodesForContinent(i + 1).size() > 2))
								{
									repeat = false;
									continue;
								}
								else
								{
									repeat = true;
									canExit = true;
									break;
								}
							}
							if (canExit)
							{
								break;
							}
						}
						if (canExit)
						{
							break;
						}
					}
					if (!canExit)
					{
						break;
					}
				}

				if (!canExit)
				{
					cout << "A territory acts as a trap.\n";
				}
				else
				{
					TerritoriesConnected = true;
				}
			}
			if (TerritoriesConnected)
			{
				cout << "Territories are connected\n";
			}
			else
			{
				cout << "Continents are not connected\n";
			}
		}

		cout << endl
			 << endl;
	}

	if (!(TerritoriesConnected && ContinentsConnected && TerritoryhasOneContinent))
	{
		cout << "The map is not valid.\n";
		return false;
	}
	return true;
}
vector<Territory> Map::getNodesForContinent(int n)
{
	vector<Territory> v;
	for (int i = 0; i < ListOfNodes->size(); i++)
	{
		if (ListOfNodes->at(i).getTerritoryContinent() == n)
		{
			v.push_back(ListOfNodes->at(i));
		}
	}

	return v;
}

//Method for identifying map file elements
int Continent::Parsing(string line, string &element1, string &element2, string &element3)
{
	stringstream ss(line);
	string word;
	int i = 0;
	while (ss >> word)
	{
		if (i == 0)
		{
			element1 = word;
		}
		if (i == 1)
		{
			element2 = word;
		}
		if (i == 2)
		{
			element3 = word;
		}
		i++;
	}
	int element2i = stoi(element2);
	return element2i;
}
int Territory::Parsing(string line, string &element1, string &element2)
{
	stringstream ss(line);
	string word;
	int i = 0;
	while (ss >> word)
	{
		if (i == 1)
		{
			element1 = word;
		}
		if (i == 2)
		{
			element2 = word;
		}
		i++;
	}
	int element2i = stoi(element2);
	return element2i;
}

//Stream Insertion Operators
ostream &operator<<(ostream &os, const Continent &c)
{
	os << "Continent Number : " << c.C_num << " , Continent Name : " << c.C_name << endl;
	return os;
}
ostream &operator<<(ostream &os, const Territory &t)
{
	string edges;
	for (int i = 0; i < t.NeighboringTerritories.size(); i++)
	{

		edges = edges + to_string(t.NeighboringTerritories.at(i)) + " ";
	}
	os << "Territory Number : " << t.T_num << " , Territory Name : " << t.T_name << " , Territory armies # : " << t.NumOfArmies << " , Territoriy leads to : " << edges << endl;

	return os;
};

//Continent Accessors
int Continent::getContinentNumber()
{
	return C_num;
};
string Continent::getContinentName()
{
	return C_name;
};
int Continent::getCCB()
{
	return CCBus;
};
string Continent::getContinentColour()
{
	return colour;
};

//Territory Accessors
int Territory::getTerritoryNumber()
{
	return T_num;
};
string Territory::getTerritoryName()
{
	return T_name;
};
int Territory::getTerritoryContinent()
{
	return Continent_Number;
}
int Territory::getPlayerNumber()
{
	return PlayerNumber;
};
vector<int> Territory::getTerritoryConnexions()
{
	return NeighboringTerritories;
}
vector<Territory *> &Territory::getEdges()
{
	return Edges;
};
int Territory::getNumOfArmies()
{
	return NumOfArmies;
}

//Map Accessors
Territory *Map::getNode(int n)
{
	return &ListOfNodes->at(n);
};
Continent *Map::getContinent(int n)
{
	return &ListOfContinents->at(n);
};

//Territory Game Related Methods
void Territory::addNeighbors(int v)
{
	//For THIS territory, adding neighbors
	NeighboringTerritories.push_back(v);
}
void Territory::setNumArmies(int n)
{
	NumOfArmies = n; // Updates the number of armies
};
void Territory::setPlayerNumber(int n)
{
	PlayerNumber = n; // Used whenever a Player gains control of a territory
};
void Territory::addEdges(Territory *p)
{
	Edges.push_back(p);
};
bool Territory::PlayerCheck(int n)
{
	return (PlayerNumber == n ? true : false); // Used whenever to check if a territory belongs to player N
};

void DummyPlayer::setPlayerNumber(int n)
{
	playerNum = n;
}
int DummyPlayer::getPlayerNum()
{
	return playerNum;
}
DummyPlayer::DummyPlayer(int n)
{
	playerNum = n;
}
