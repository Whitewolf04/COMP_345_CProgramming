#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


class Continent {
	private:
		int C_num;
		string C_name;
		int CCBus;
		string colour;
	public:
		//Constructors
		Continent(int i, string s, int i2, string s2);
		Continent(const Continent& c);
		Continent& operator =(const Continent& c); // Not Working Properly

		//Accessors
		int getContinentNumber();
		string getContinentName() ;
		int getCCB();
		string getContinentColour();
		

		//Stream Insertion Operator
		friend ostream& operator<<(ostream& os, const Continent& dt);

		//Method for reading map file
		static int Parsing(string line, string& element1, string& element2, string& element3);

};

class DummyPlayer {
private:
	int playerNum;
public:
	DummyPlayer(int n);
	void setPlayerNumber(int n);
	int getPlayerNum();
};

class Territory {
	
	private:
		int T_num;
		int NumOfArmies;
		string T_name;
		int Continent_Number;
		int PlayerNumber=0;
		vector<int> NeighboringTerritories;
		vector<Territory*> Edges;

	public:
		//Constructors
		Territory();
		Territory(int num, int armies, string name, int Cont_num);
		Territory(const Territory& t);
		Territory& operator = (const Territory& t);// Not Working Properly

		//Accessors
		int getTerritoryNumber();
		string getTerritoryName();
		int getTerritoryContinent();
		int getPlayerNumber();
		int getNumOfArmies();
		vector<int> getTerritoryConnexions();
		vector<Territory*>& getEdges();

		//Mutator
		void addNeighbors(int n);
		void setNumArmies(int n);
		void setPlayerNumber(int n);
		void addEdges(Territory* p);

		//Checking if territory belongs to the passed player
		bool PlayerCheck(int n);

		//Stream Insertion Operator
		friend ostream& operator<<(ostream& os, const Territory& dt);
		//Method for reading map file
		static int Parsing(string line, string& element1, string& element2);

};




class Map {


	public:	
		//Constructors and destructor
		Map(std::string name);
		Map(const Map& m);
		Map(vector<Continent>& v, vector<Territory>& t);
		//Display Methods
		void printContinentList();
		void printNodeList();
		vector<Territory> getNodesForContinent(int n);
		
		//Game Related Methods
		bool advance(int n, int m);
		bool PlayerCheck(int node, int playerN);
		bool validate();

		//Accessors
		Territory* getNode(int n);
		Continent* getContinent(int n);
	private:
		vector<Territory>* ListOfNodes = new vector<Territory>;
		vector<Continent>* ListOfContinents = new vector<Continent>;

};

class MapLoader {

	public:
		static string FileLoader(ifstream* stream,string name); // Checks if file exists
		static bool FileParser(string& str, vector<Continent>& v, vector<Territory>& c); // Add function to empty v and c if map is invalid

	private:
		static void addContinents(Continent c, vector<Continent>* v);
		static void addTerritory(Territory t, vector<Territory>* v);
		vector<Continent>* Continents;
		vector<Territory>* CountryList;
};

//Add dummy player class
//validate method
