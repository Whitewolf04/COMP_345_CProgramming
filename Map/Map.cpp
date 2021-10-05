#include "Map.h"

using namespace std;


string MapLoader::FileLoader(ifstream* stream)
{
	string* Mapname = new string();
	ifstream* fs = stream;
	cout << "Enter the name of the map you wish to use." << endl;
	cin >> *Mapname;
	cout << "Opening " << *Mapname << " file for Parsing...." << endl;

	fs->open(*Mapname);
	if (*fs) {
		cout << "file exists\nProceeding with the file parsing\n";
	}
	else {
		cout << "file doesn't exist\n";
		cout << "Exiting for safety reasons...";
		exit(0);
	}

	return string((std::istreambuf_iterator<char>(*fs)), std::istreambuf_iterator<char>());
}
void MapLoader::FileParser(string& str, vector<Continent>& c, vector<Territory>& t)
{
	
	//Making pointers to passed varaibles
	string* file = &str;
	vector<Continent>* C = &c;
	vector<Territory>* T = &t;
	//Making variables that will be used to read from the input string
	istringstream stream(*file);
	string* line = new string();
	//Initializing local scope variables
	int order = 0;
	int ContinentOrder = 1;
	int TerritoryOrder = 1;
	int NodeNumber = 0;
	bool valid = true;
	bool ContinentMark = false;
	bool TerritoryMark = false;
	bool BorderMark = false;

	while (getline(stream, *line)) {
		//If the file is marked as invalid anywhere down below, it will empty the values of Continent and Territory passed vectors
		//The reason they are emptied is to make it possible for them to be re-used if needed.
		if (!valid) {
			cout << "Invalid file... Discarting Input Map\n";
			cout << "Emptying Continent List\n";
			C->clear();
			cout << "Emptying Territory List\n";
			T->clear();
			break;
		}
		//Following section basically checks if the file format for the maps is the correct one
		if (*line == "[continents]") {
			order = 1;
			continue;
		}
		else if (*line == "[countries]" && ContinentMark) { 
			// After the continents section is checked, the Territories section will be checked
			// For the Territories to be checked in the first place, the Continent section needs to have been valid
			order = 2;
			continue;
		}
		else if (*line == "[countries]" && !ContinentMark) {
			cout << "The file is missing a section...\n";
			valid = false;
			continue;
		}
		else if (*line == "[borders]" && TerritoryMark && ContinentMark) {
			order = 3;
			continue;
		}
		else if (*line == "[borders]" && (!ContinentMark || !TerritoryMark)) {
			cout << "The file is missing a section...\n";
			valid = false;
			continue;
		}
		
		if (order == 1 && *line != "") {

			//Extrapolating the Information from the File for Use
			string* NameOfContinent = new string();string* NumberOfArmies = new string();string* Colour = new string();
			int IntegerAmountOfArmies;
			try { IntegerAmountOfArmies = Continent::Parsing(*line, *NameOfContinent, *NumberOfArmies, *Colour); } //Accepts floats, 2 fix l8r, if colour missing, still works
			catch (exception e) {
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
		else if (order == 1 && *line == "") {
			ContinentMark = true; //Continent section has been fully parsed
			order = 0;
		}
		else if (order == 2 && *line != "") {

			//Extrapolating the Information from the File for Use
			string* NameOfTerritory = new string();string* ContinentNumberofTerritory = new string();int IntegerNumberOfContinent;
			try { IntegerNumberOfContinent = Territory::Parsing(*line, *NameOfTerritory, *ContinentNumberofTerritory); }
			catch (exception e) {
				cout << "Parsing error at Territory Section, Invalid format..\n";
				valid = false;
				continue;
			}

			//Accessing the amount of armies that each continent has for its armies
			int numOfArmies = C->at(IntegerNumberOfContinent -1).getContinentArmies();

			//Adding a Territory Object with the Above Values to the passed Vector of Territories
			Territory t(TerritoryOrder, numOfArmies, *NameOfTerritory, IntegerNumberOfContinent);
			MapLoader::addTerritory(t, T);
			TerritoryOrder++;

			//Avoiding MLeak
			delete NameOfTerritory, ContinentNumberofTerritory,t;

		}
		else if (order == 2 && *line == "") {
			TerritoryMark = true; //Territory section has been fully parsed
			order = 0;
		}
		else if (order == 3 && *line != "") {

			BorderMark = true;
			//Parsing the file for the Values of Each Border
			stringstream ss(*line);string word; // Needed to read each line
			vector<int> Connexions; // Temporarly stores all connexions of a specific node
			int i = 0;int j = 0;

			while (ss >> word) {
				//Avoids the first value (It's the node number representing each Territory)
				if (j == 0) { j++; continue; }

				//Adds the neighboring nodes to the Connexions vector defined above
				try { Connexions.push_back(stoi(word)); } //Try catch used to avoid non-integer values added
				catch (exception e) {
					cout << "Parsing error at Border Section, Invalid format..\n";
					valid = false;
					break;
				}
			}
			if (valid) {
				for (int i = 0;i < Connexions.size();i++) {
					//Adds the value of the Connexions vector defined above to the corresponding node (NodeNumber)
					//For the Node 1, it will add whatever has been identified in the while loop and added to Connexions
					//For the Node 2, it will do the same for that line, etc..
					T->at(NodeNumber).addNeighbors(Connexions.at(i));
				}
			}
			NodeNumber++;
			
		}
		
	
	}
	if ((!ContinentMark || !TerritoryMark || !BorderMark) && valid) { //checks if all sections have been identified, if not cancels the map loading
		cout << "Invalid file... Discarting Input Map\n";
		cout << "Emptying Continent List\n";
		C->clear();
		cout << "Emptying Territory List\n";
		T->clear();
	};
	
}

//Definiton of Methods to add Continents and Territories to the passed vectors (Arguments : C/T object and C/T Vectors)
void MapLoader::addContinents(Continent c, vector<Continent>* v) {
	v->push_back(c);
}
void MapLoader::addTerritory(Territory t, vector<Territory>* v) {
	v->push_back(t);
}

//Constructor//AssignmentOperator Definitions
Territory::Territory(int i, int i2, string s, int i3) {
	T_num = i;
	NumOfArmies = i2;
	T_name = s;
	Continent_Number = i3;
}
Territory::Territory(const Territory& t) {
	T_num = t.T_num;
	NumOfArmies = t.NumOfArmies;
	T_name = t.T_name;
	Continent_Number = t.Continent_Number;
}
Territory &Territory::operator=(const Territory& t) {
	return *this; }

Continent::Continent(int i, string s, int i2, string s2) {
	C_num = i;
	C_name = s;
	NumOfArmies = i2;
	colour = s2;
}
Continent::Continent(const Continent& c) {
	C_num = c.C_num;
	C_name = c.C_name;
	NumOfArmies = c.NumOfArmies;
	colour = c.colour;
}
Continent& Continent::operator=(const Continent& t) { return *this; }

//Method for identifying map file elements
int Continent::Parsing(string line,string& element1, string& element2, string& element3) {
	stringstream ss(line);
	string word;
	int i = 0;
	while (ss >> word) {
		if (i == 0) { element1 = word; }
		if (i == 1) { element2 = word; }
		if (i == 2) { element3 = word; }
		i++;
	}
	int element2i = stoi(element2);
	return element2i;
}
int Territory::Parsing(string line, string& element1, string& element2) {
	stringstream ss(line);
	string word;
	int i = 0;
	while (ss >> word) {
		if (i == 1) { element1 = word; }
		if (i == 2) { element2 = word; }
		i++;
	}
	int element2i = stoi(element2);
	return element2i;
}

//Stream Insertion Operators
ostream& operator<<(ostream& os, const Continent& c)
{
	os << "Continent Number : " << c.C_num << " , Continent Name : " << c.C_name << endl;
	return os;
}
ostream& operator<<(ostream& os, const Territory& t) {
	string edges;
	for (int i = 0; i < t.NeighboringTerritories->size();i++) {
		edges = edges + to_string(t.NeighboringTerritories->at(i)) + " ";
	}
	os << "Territory Number : " << t.T_num << " , Territory Name : " << t.T_name << " , Territory armies # : " << t.NumOfArmies << " , Territoriy leads to : " << edges << endl;

	return os;
};

//Continent Accessors
int Continent::getContinentNumber() {
	return C_num;
};
string Continent::getContinentName() {
	return C_name;
};
int Continent::getContinentArmies() {
	return NumOfArmies;
};
string Continent::getContinentColour() {
	return colour;
};

//Territory Accessors
int Territory::getTerritoryNumber() {
	return T_num;
};
string Territory::getTerritoryName() {
	return T_name;
};
int Territory::getTerritoryContinent() {
	return Continent_Number;
}
int Territory::getPlayerNumber() {
	return PlayerNumber;
};
vector<int>& Territory::getTerritoryConnexions() {
	return *NeighboringTerritories;
}

//Territory Mutators
void Territory::addNeighbors(int v) {
	//For THIS territory, adding neighbors
	NeighboringTerritories->push_back(v);
}
void Territory::setNumArmies(int n) {
	NumOfArmies = n; // Updates the number of armies
};
void Territory::setPlayerNumber(int n) {
	PlayerNumber = n;
};

bool Territory::PlayerCheck(int n) {
	return (PlayerNumber==n ? true : false);
};

