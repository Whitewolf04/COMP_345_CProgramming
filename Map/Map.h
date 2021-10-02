#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class Continent {
	private:
		int C_num;
		string C_name;
		int NumOfArmies;
		string colour;
	public:
		//Constructors
		Continent(int i, string s, int i2, string s2);
		Continent(const Continent& c);
		Continent& operator =(const Continent& c); // Not Working Properly

		//Accessors
		int getContinentNumber();
		string getContinentName() ;
		int getContinentArmies();
		string getContinentColour();

		//Stream Insertion Operator
		friend ostream& operator<<(ostream& os, const Continent& dt);

		//Method for reading map file
		static int Parsing(string line, string& element1, string& element2, string& element3);

};

class Territory {
	private:
		int T_num;
		int NumOfArmies;
		string T_name;
		int Continent_Number;
		int PlayerNumber;
		vector<int>* NeighboringTerritories = new vector<int>;
	public:
		//Constructors
		Territory(int num, int armies, string name, int Cont_num);
		Territory(const Territory& t);
		Territory& operator = (const Territory& t);// Not Working Properly

		//Accessors
		int getTerritoryNumber();
		string getTerritoryName();
		int getTerritoryContinent();
		int getPlayerNumber();
		vector<int>& getTerritoryConnexions();

		//Mutator
		void addNeighbors(int n);
		void setNumArmies(int n);
		void setPlayerNumber(int n);

		//Checking if territory belongs to the passed player
		bool PlayerCheck(int n);

		//Stream Insertion Operator
		friend ostream& operator<<(ostream& os, const Territory& dt);
		//Method for reading map file
		static int Parsing(string line, string& element1, string& element2);

};

struct Node {

	
};
class Map {

	public:	

	private:

};

class MapLoader {

	public:
		static string FileLoader(ifstream* stream); // Checks if file exists
		static void FileParser(string& str, vector<Continent>& v, vector<Territory>& c); // Add function to empty v and c if map is invalid

	private:
		static void addContinents(Continent c, vector<Continent>* v);
		static void addTerritory(Territory t, vector<Territory>* v);
		vector<Continent>* Continents;
		vector<Territory>* CountryList;
};