#include "CommandProcessing.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "PlayerStrategies.h"
#include "Cards.h"


#include <ostream>
#include <istream>
#include <typeinfo>
using namespace std;


const map <GameState, string> gsmap = {{startup, "startup"}, {play, "play"}};
const map <StartupManagerState, string> smsmap = {{start, "start"}, {mapLoaded, "mapLoaded"}, {mapValidated, "mapValidated"}, {playersAdded, "playersAdded"}, {finishSMS, "finishSMS"}};
const map <PlayManagerState, string> pmsmap = {{assignReinforcement,"assignReinforcement"},{issueOrders, "issueOrders"}, {executeOrders, "executeOrders"}, {win, "win"}, {finishPMS, "finishPMS"}};

bool isGameOver = false;
bool winnerFound = false;

vector<Player*> listOfPlayers;
vector<Player*> orderedListOfPlayers;

// REMEMBER TO ADD DELETE STATEMENT LATER
//---------------------------------------------------------

Deck * deck = new Deck(60);

Map * loader;

GameState gs;

State s;

CommandProcessor* cp;
int readCounter = 0;

string CommandProcessor::readCommand() {
    string commandstr;
    getline(cin, commandstr);
    return commandstr;
}

// void CommandProcessor::saveCommand(string c, string e) {
void CommandProcessor::saveCommand(string c) {
    Command cmd(c);
    lc.push_back(cmd);
}

void CommandProcessor::showList() {
    for (int i = 0; i < lc.size(); i ++) {
        cout << lc[i].toString() << "\n";
    }
}

string CommandProcessor::getCommand() {
    string cmd;
    cmd = readCommand();
    saveCommand(cmd);
    return cmd;
}

bool CommandProcessor::validate(State st, string cmd) {
    string c = cmd.substr(0,cmd.find(' '));
    if (c == "loadmap" && (st == START || st == MAPLOADED)) {
        cout << "Valid command. " << "\n";
        return true;
    }
    if (c == "validatemap" && st == MAPLOADED) {
        cout << "Valid command. " << "\n";
        return true;
    }
    if (c == "addplayer" && (st == MAPVALIDATED || st == PLAYERADDED)) {
        cout << "Valid command. " << "\n";
        return true;
    }
    if (c == "gamestart" && st == PLAYERADDED) {
        cout << "Valid command. " << "\n";
        return true;
    }
    if (c == "replay" && st == WIN) {
        cout << "Valid command. " << "\n";
        return true;
    }
    if (c == "quit" && st == WIN) {
        cout << "Valid command. " << "\n";
        return true;
    }
    cout << "Invalid input, please enter a valid option" << "\n";
    return false;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string f) {
    fileName = f;
}
string FileCommandProcessorAdapter::readCommand() {
    string commandstr;
    commandstr = flr.readLineFromFile(fileName);
    return commandstr;
}
string FileLineReader::readLineFromFile(string fileName) {
    ifstream file(fileName);
    string line;
    for (int i = 0; i <= readCounter; i++) {
        getline(file, line);
    }
    readCounter++;
    return line;
}

Command::Command(string c) {
    command = c;
}

void Command::saveEffect(string e) {
    effect = e;
}

string Command::toString() {
    return "command: " + command + ", effect: " + effect;
}

void StartupManager::printSMS() {
    cout << "The game is in " << gsmap.at(gs) << " state at the " << smsmap.at(sms) << " sub-state." << "\n";
}
void StartupManager::setSms(StartupManagerState s) {
    sms = s;
}
void StartupManager::init () {
    cout << "\n";
    cout << "Do you want to enter commands from the text file or from the console? Type t/c" << "\n";
    string select;
    cin >> select;
    if (select == "t") {
        cp = new FileCommandProcessorAdapter("command.txt");
    }
    else if (select == "c") {
        cp = new CommandProcessor();
        cin.ignore(1);
    }
    else {
        cout << "Wrong input, now using the console by default." << "\n";
        cp = new CommandProcessor();
        cin.ignore(1);
    }
    gs = startup;
    setSms(start);
    s = START;
    printSMS();
    cout << "Please enter an option" << "\n";
    string input = cp->getCommand();
    while (!cp->validate(s, input)) {
        cp->lc.back().saveEffect("Error. Nothing happened.");
        input = cp->getCommand();
    }
    string arg = input.substr(input.find(' ') + 1, input.length()-1);
    cout << "Loading the map " + arg << "\n";
    cp->lc.back().saveEffect("Loading the map " + arg);
    transition();
    mapLoad(arg);
}
void StartupManager::mapLoad(string arg) {
    cout << "\n";
    // load map
    loader = new Map(arg);
    // load map
    setSms(mapLoaded);
    s = MAPLOADED;
    printSMS();
    cout << "Please enter an option" << "\n";
    string input = cp->getCommand();
    while (!cp->validate(s,input) || input.substr(0,input.find(' ')) == "loadmap") {
        if (input == "loadmap") {
            cout << "Loading the map" + arg+ "\n";
            // loadmap
            loader = new Map(arg);
            // loadmap
            cp->lc.back().saveEffect("Loading the map " + arg + "\n");
            printSMS();
            cout << "Please enter an option" << "\n";
        }
        else {
            cout << "Error. Nothing happened." << "\n";
            cp->lc.back().saveEffect("Error. Nothing happened.");
        }
        input = cp->getCommand();
    }
    if (input == "validatemap") {
        cout << "Validating the map." << "\n";
        cp->lc.back().saveEffect("Validating the map.");
        transition();
        validateMap();
    }
}
void StartupManager::validateMap() {
    cout << "\n";
    // validate map
    loader->validate();
    // validatemap
    setSms(mapValidated);
    s = MAPVALIDATED;
    printSMS();
    cout << "Please enter an option" << "\n";
    string input = cp->getCommand();
    while (!cp->validate(s, input)) {
        cp->lc.back().saveEffect("Error. Nothing happened.");
        input = cp->getCommand();
    }

    string arg = input.substr(10, (input.find("-t")-1)-10);
    string arg2 = input.substr(input.find("-t")+3, input.size()-1);

    cp->lc.back().saveEffect("Adding player " + arg);
    transition();
    addPlayers(arg, arg2);
}
void StartupManager::addPlayers(string arg, string arg2) {
    cout << "\n";
    Player* p;
    // add player
    if(arg2 == "Human" || arg2 == "human"){
        p = new Player(arg, new Human(), arg2);
    }else if(arg2 == "Neutral" || arg2 == "neutral"){
        p = new Player(arg, new Neutral(), arg2);
    }else if (arg2 == "Aggressive" || arg2 == "aggressive"){
        p = new Player(arg, new Aggressive(), arg2);
    }else if (arg2 == "Cheater" || arg2 == "cheater"){
        p = new Player(arg, new Cheater(), arg2);
    }else if (arg2 == "Benevolent" || arg2 == "benevolent"){
        p = new Player(arg, new Benevolent(), arg2);
    }else{
        cout << "Input strategy does not exist, we will select Human by default" << '\n';
        p = new Player(arg, new Human(), "Human");
    }
    listOfPlayers.push_back(p);
//    Player::addPlayer(p);
    // add player
    setSms(playersAdded);
    s = PLAYERADDED;
    printSMS();
    cout << "Please enter an option" << "\n";
    string input = cp->getCommand();
    cout << input << "\n";
    while (!cp->validate(s, input) || input.substr(0,input.find(' ')) == "addplayer" ) {
        if (input.substr(0,input.find(' ')) == "addplayer") {
            string name = input.substr(10, (input.find("-t")-1)-10);
            string type = input.substr(input.find("-t")+3, input.size()-1);

            cp->lc.back().saveEffect("Adding player "+ name);
            // add player
            if(type == "Human" || type == "human"){
                p = new Player(name, new Human(), type);
            }else if(type == "Neutral" || type == "neutral"){
                p = new Player(name, new Neutral(), type);
            }else if (type == "Aggressive" || type == "aggressive"){
                p = new Player(name, new Aggressive(), type);
            }else if (type == "Cheater" || type == "cheater"){
                p = new Player(name, new Cheater(), type);
            }else if (type == "Benevolent" || type == "benevolent"){
                p = new Player(name, new Benevolent(), type);
            }else{
                cout << "Input strategy does not exist, we will select Human by default" << '\n';
                p = new Player(name, new Human(), "Human");
            }
            listOfPlayers.push_back(p);
//            Player::addPlayer(p);
            //
            printSMS();
            cout << "Please enter an option" << "\n";
        }
        else {
            cp->lc.back().saveEffect("Error. Nothing happened.");
        }
        input = cp->getCommand();
    }
    cout << "Assigning countries" << "\n";
    cp->lc.back().saveEffect("Assigning countries");
    transition();
    gameStart();
}
void StartupManager::gameStart() {
    cout << "\n";
    // gamestart
    // distribute territories
    int numOfPlayers = listOfPlayers.size();
    int mapSize = loader->getSize();
    int division = mapSize / numOfPlayers;
    int remainder = mapSize % numOfPlayers;
    int constant = division;


    for (int i = 0; i < numOfPlayers; i++) {

        if(i == 0){
            listOfPlayers.at(i)->playerTerritories.push_back(loader->getNode(0));
            listOfPlayers.at(i)->playerTerritories.push_back(loader->getNode(1));

            loader->getNode(0)->setPlayerNumber(listOfPlayers.at(i)->getId());
            loader->getNode(1)->setPlayerNumber(listOfPlayers.at(i)->getId());
        }else{
            listOfPlayers.at(i)->playerTerritories.push_back(loader->getNode(division-1));
            listOfPlayers.at(i)->playerTerritories.push_back(loader->getNode(division));

            loader->getNode(division-1)->setPlayerNumber(listOfPlayers.at(i)->getId());
            loader->getNode(division)->setPlayerNumber(listOfPlayers.at(i)->getId());
            division += constant;
        }
    }
    loader->convertToPointers();
    // determine order
    int x;
    map <int, string> pipi;
    for (int i = 0; i < numOfPlayers; i++) {
        x = rand() % numOfPlayers;
        if (pipi[x] == "") {
            orderedListOfPlayers.push_back(listOfPlayers.at(x));
            pipi[x] = listOfPlayers.at(x)->getPlayerName();
        }
        else {
            i--;
        }
    }
    // give armies
    for (int i = 0; i < orderedListOfPlayers.size(); i++) {
        orderedListOfPlayers.at(i)->addReinArmy(50);
    }
    // make each play draw
    for (int i = 0; i < orderedListOfPlayers.size(); i++) {
        orderedListOfPlayers.at(i)->playerHand->drawCard(deck);
        orderedListOfPlayers.at(i)->playerHand->drawCard(deck);
    }
    // gamestart
    setSms(finishSMS);
    gs = play;
    cout << "End of startup phase." << "\n\n\n";
    cout << "Thank you for your patience. The game shall now startup!\n";
}

void PlayManager::printPMS() {
    cout << "The game is in " << gsmap.at(gs) << " state at the " << pmsmap.at(pms) << " sub-state." << "\n";
}
void PlayManager::setPms(PlayManagerState p) {
    pms = p;
}

void PlayManager::gameLoop(){
    while(!winnerFound){
        init();
        issueOrder();
        exeOrder();

        for(int i = 0; i < listOfPlayers.size(); i++){
            Player * temp = listOfPlayers.at(i);
            if(checkWinner(temp)){
                cout << "Player " << temp->getPlayerName() << " has won the game!!!!" << endl;
                winnerFound = true;
                break;
            }
        }
    }

    // If a winner has been found, call win() method
    wins();
}

// Reinforcement phase
void PlayManager::init () {
    setPms(assignReinforcement);
    s = ASSIGNREINFORCEMENT;
    printPMS();
    // Reinforcement phase starts
    for(int i = 0; i < listOfPlayers.size(); i++){
        // Avoid null pointer issues
        if(listOfPlayers.at(i) == nullptr){continue;}

        Player* temp =  listOfPlayers.at(i);
        int reinArmyNum = (int) ((*temp).playerTerritories.size() / 3);

        // Make sure that each player receive minimum 3 reinforcement armies
        if(reinArmyNum <= 3){
            reinArmyNum = 3;
        }
        (*temp).addReinArmy(reinArmyNum);

        // Consider continent quirk
        for(int k = 0; k < loader->getListOfContinents().size(); k++){
            bool owned = true;
            int continentNum = loader->getListOfContinents().at(k).getContinentNumber();
            for(int j = 0; j < loader->getNodesForContinent(continentNum).size(); j++){
                int playerID = temp->getId();
                Territory tempTerritory = loader->getNodesForContinent(continentNum).at(j);
                if(!tempTerritory.PlayerCheck(playerID)){
                    owned = false;
                    break;
                }
            }

            if(owned){
                cout << "Player " << temp->getPlayerName() << " owns continent " << loader->getListOfContinents().at(k).getContinentName() << ", so bonus will be given" << endl;
                reinArmyNum += loader->getListOfContinents().at(k).getCCB();
            }
        }

        cout << "DEBUG: " << (*temp).getPlayerName() << " has " << (*temp).getReinArmy() << " armies in the reinforcement pool." << endl;
    }

    // Reinforcement phase is done, move on to the next phase on command
//    issueOrder();
}

// Issuing order phase
void PlayManager::issueOrder(){
    cout << "\n";
    // Start issue order phase, print out the current game state
    setPms(issueOrders);
    s = ISSUEORDER;
    printPMS();

    cout << "Here's a look into the map for this turn" << '\n';
    loader->printNodeList();
    // Ask user to issue order
    for(int i = 0; i < listOfPlayers.size(); i++){
        // Prevent NULL pointer issue
        if(listOfPlayers.at(i) == nullptr){continue;}

        Player* tempPlayer = listOfPlayers.at(i);
        bool endIssueOrder = false;

        // Print out user's name and ask to issue order
        cout << "Player " << tempPlayer->getPlayerName() << ", it is your turn to issue order." << endl;



        if(tempPlayer->getStrategy() == "Human"){
            // Loop constantly until the current player has finished issuing order
            while(!endIssueOrder) {
                string input;

                // Check if player has reinforcement army
                // Might have issues with territory to defend vector
                if(tempPlayer->getReinArmy() > 0) {
                    cout << "You still have armies in the reinforcement pool, please deploy before you can issue any other order!" << endl;

                    // Print out territories that player can deploy army
                    cout << "These are the territories that you can deploy to: " << endl;
                    vector<Territory *> territoryToDefend = tempPlayer->playerTerritories;
                    for (int k = 0; k < territoryToDefend.size(); k++) {
                        territoryToDefend[k]->setPlayerNumber(tempPlayer->getId());
                        cout << territoryToDefend[k]->getTerritoryName() << endl;
                    }

                    // Check for valid order
                    while (true){
                        // Fetch order from the player
                        cout << "Please enter an order: ";
                        cin >> input;
                        cout << "\n" << endl;

                        if(input == "deploy"){
                            //Choose army count

                            int deploy;
                            while (true)
                            {
                                cout << "Enter number of army to deploy: " << '\n';
                                cin >> deploy;
                                if(deploy <= tempPlayer->getReinArmy() && deploy>0){
                                    break;
                                }else{
                                    cout << "Invalid army count" << '\n';
                                }
                            }
                            //Choose territory
                            int t_deploy;
                            while (true)
                            {
                                cout << "Enter territory id to deploy to: " << '\n';
                                cin >> t_deploy;
                                if(t_deploy <= territoryToDefend.size() && t_deploy>0){
                                    break;
                                }else{
                                    cout << "Invalid territory" << '\n';
                                }
                            }

                            Deploy * newOrder = new Deploy(deploy, territoryToDefend.at(t_deploy-1) ,tempPlayer->getId());

                            if(newOrder->validate()){
                                tempPlayer->removeReinArmy(newOrder->getArmyCount());
                            }
                            cout << newOrder->execute() << '\n';
                            break;
                        } else{
                            cout << "Invalid order. Please try again!" << endl;
                        }
                    }

                    // After order is issued, loop back to get other orders from the player
                    continue;
                }

                // Notify the player if they don't need to deploy
                cout << "You have no reinforcement army to deploy, you can proceed with other orders" << endl;
                // List the territories that the player can attack
                cout << "These are the territories that you can attack: " << endl;
                loader->printNodeList();
                //vector<Territory> territoryToAttack = loader->getNodesForContinent();
                //for (int k = 0; k < territoryToAttack.size(); k++) {
                //    cout << territoryToAttack[k]->getTerritoryName() << endl;
                //}
                cout << endl;

                // Fetch order from the player
                cout << "Please enter an order: ";
                cin >> input;
                cout << "\n" << endl;

                string cardName;
                // Check if the player is playing a card or issuing an order
                if(input.substr(0,input.find(' ')) == "playcard"){
                    cardName = input.substr(input.find(' ') + 1, input.length()-1);

                    // Check if the card is valid
                    while(true){
                        if(tempPlayer->playerHand->contains(cardName)){
                            break;
                        } else{
                            cout << "You don't have that card on your hand!" << endl;
                            cout << R"(Input "exit" to return to order. Input "tryagain" to try again!)" << endl;
                            cin >> input;
                            cout << endl;

                            // Check user's choice
                            if(input == "exit"){
                                cardName = "NULL";
                                break;
                            } else if(input == "tryagain"){
                                cout << "Please enter the card you want to play: ";
                                cin >> input;
                                cout << "\n" << endl;
                                cardName = input;
                            } else {
                                cout << "Invalid input. Please try again!" << endl;
                            }
                        }
                    }

                    // Check if the player wants to exit play card
                    if(cardName == "NULL"){
                        continue;
                    }

                    // Play card feature to be implemented
                    cout << "Card " << cardName << " has been played" << endl;
                } else {
                    // Create a new order and check if it is valid
                    if(input == "advance"){
                        int sourceId;
                        int adjacentId;

                        while(true){
                            cout << "Choose source territory to advance from: " << endl;
                            cin >> sourceId;
                            cout << "Choose adjacent territory to advance to: " << endl;
                            cin >> adjacentId;

                            if(sourceId <= loader->getSize() && sourceId > 0 && adjacentId <= loader->getSize() && adjacentId > 0){
                                break;
                            }else{
                                cout << "Invalid territory ID" << endl;
                            }
                        }

                        Advance * newOrder = new Advance(loader->getAllTerritoriesP().at(sourceId-1),loader->getAllTerritoriesP().at(adjacentId-1), tempPlayer->getId());
                        tempPlayer->issueOrder(newOrder);
                    } else if(input == "deploy"){
                        //Choose army count
                        int deploy;
                        while (true)
                        {
                            cout << "Enter number of army to deploy: " << '\n';
                            cin >> deploy;
                            if(deploy <= tempPlayer->getReinArmy() && deploy>=0){
                                break;
                            }else{
                                cout << "Invalid army count" << '\n';
                            }
                        }
                        //Choose territory
                        int t_deploy;
                        while (true)
                        {
                            cout << "Enter territory id to deploy to: " << '\n';
                            cin >> t_deploy;
                            if(t_deploy <= loader->getAllTerritoriesP().size() && t_deploy>0){
                                break;
                            }else{
                                cout << "Invalid territory" << '\n';
                            }
                        }

                        Deploy * newOrder = new Deploy(deploy, loader->getAllTerritoriesP().at(t_deploy-1) ,tempPlayer->getId());
                        tempPlayer->issueOrder(newOrder);
                    } else if(input == "bomb"){
                        cout << cardName << '\n';
                        int sourceId;
                        int adjacentId;

                        while(true){
                            cout << "Choose source territory to bomb from: " << endl;
                            cin >> sourceId;
                            cout << "Choose adjacent territory to bomb to: " << endl;
                            cin >> adjacentId;

                            if(sourceId <= loader->getSize() && sourceId > 0 && adjacentId <= loader->getSize() && adjacentId > 0){
                                break;
                            }else{
                                cout << "Invalid territory ID" << endl;
                            }
                        }

                        Bomb * newOrder = new Bomb(loader->getAllTerritoriesP().at(sourceId-1),loader->getAllTerritoriesP().at(adjacentId-1), tempPlayer->getId());
                        tempPlayer->issueOrder(newOrder);
                    } else if(input == "blockade"){
                        int sourceId;

                        while(true){
                            cout << "Choose territory to blockade" << endl;
                            cin >> sourceId;
                            if(sourceId <= loader->getSize() && sourceId > 0){
                                break;
                            }else{
                                cout << "Invalid territory ID" << endl;
                            }
                        }

                        Blockade * newOrder = new Blockade(loader->getAllTerritoriesP().at(sourceId-1),tempPlayer->getId());
                        tempPlayer->issueOrder(newOrder);
                    } else if(input == "airlift"){
                        //Choose territory

                        int source;
                        int target;
                        while (true)
                        {
                            cout << "Enter territory id to deploy from: " << '\n';
                            cin >> source;
                            cout << "Enter territory id to deploy to: " << '\n';
                            cin >> target;
                            if(source <= loader->getAllTerritoriesP().size() && source>0 && target>0 && target <= loader->getAllTerritoriesP().size()){
                                break;
                            }else{
                                cout << "Invalid territory" << '\n';
                            }
                        }

                        //Choose army count

                        int deploy;
                        while (true)
                        {
                            cout << "Enter number of army to airlift: " << '\n';
                            cin >> deploy;
                            if(deploy>=0 && deploy <= loader->getAllTerritoriesP().at(source-1)->getNumOfArmies()){
                                break;
                            }else{
                                cout << "Invalid army count, army needs to be smaller than " << loader->getAllTerritoriesP().at(source-1)->getNumOfArmies() <<'\n';
                            }
                        }


                        Airlift * newOrder = new Airlift(deploy, loader->getAllTerritoriesP().at(source-1), loader->getAllTerritoriesP().at(target-1) ,tempPlayer->getId());
                        tempPlayer->issueOrder(newOrder);
                    } else if(input == "negotiate"){
                        int player2_id;
                        while (true)
                        {
                            cout << "Enter id of the player you want to negotiate with: " << '\n';
                            cin >> player2_id;
                            if(player2_id < listOfPlayers.size()){
                                break;
                            }else{
                                cout << "Invalid user id" << '\n';
                            }
                        }
                        Negotiate * newOrder = new Negotiate(player2_id, tempPlayer->getId());
                        tempPlayer->issueOrder(newOrder);
                    } else {
                        cout << "Invalid order! Please try again!" << endl;
                        continue;
                    }
                }

                // Ask player if they want to continue issuing order
                while (true) {
                    cout << "Do you want to end your turn? [Y/N]" << "\n";
                    cin >> input;
                    cout << endl;

                    // Check player's answer
                    if (input == "Y") {
                        endIssueOrder = true;
                        break;
                    } else if (input == "N") {
                        break;
                    } else {
                        cout << "Invalid input. Please try again!" << endl;
                    }
                }
            }
        }else if(tempPlayer->getStrategy() == "Cheater"){
            Advance* key = new Advance();
            tempPlayer->issueOrder(key);
            delete key;
        }else if(tempPlayer->getStrategy() == "Benevolent"){
            if(tempPlayer->getReinArmy() > 0){
                Deploy* key = new Deploy();
                tempPlayer->issueOrder(key);
                delete key;
            }else{
                Advance* key = new Advance();
                tempPlayer->issueOrder(key);
                delete key;
            }
        }else if(tempPlayer->getStrategy() == "Neutral"){
            Advance* key = new Advance();
            tempPlayer->issueOrder(key);
            delete key;
        }else if(tempPlayer->getStrategy() == "Aggressive"){
            if(tempPlayer->getReinArmy() > 0){
                Deploy* key = new Deploy();
                tempPlayer->issueOrder(key);
                delete key;
            }else{
                Advance* key = new Advance();
                tempPlayer->issueOrder(key);
                delete key;
            }
        }
    }
}

// Executing order phase
void PlayManager::exeOrder() {
    cout << "\n";
    // execute order
    setPms(executeOrders);
    s = EXECUTEORDERS;
    printPMS();

    for(int i = 0; i < listOfPlayers.size(); i++){
        bool first = true;
        int friend1 = -1;
        int friend2 = -2;
        Player * tempPlayer = listOfPlayers.at(i);

        // Take all of this player's order from orders list
        for(int k = 0; k < tempPlayer->playerOrdersList->getSize(); k++){
            Order* tempOrder = tempPlayer->playerOrdersList->getElement(k);

            // Check for order type
            // Assuming all orders are valid because order is checked from the previous steps

            //Apply special conditions if needed else just execute
            if(tempOrder->getType() == "advance"){
                Advance* p = (Advance*) tempOrder;
                if((p->getSourceT()->getPlayerNumber() == friend1 || p->getSourceT()->getPlayerNumber() == friend2) &&
                   (p->getAdjacentT()->getPlayerNumber() == friend1 || p->getAdjacentT()->getPlayerNumber() == friend2)){
                    cout << "You cannot attack an ally" << endl;
                }
                cout << tempOrder->execute() << '\n';
                if(p->getAdjacentT()->getNumOfArmies() == 0){
                    cout << "You won a battle" << endl;
                    //Draw a card
                    if(first){
                        tempPlayer->playerHand->drawCard(deck);
                        cout << "You gain a card" << endl;
                        first = false;
                    }
                    //Give territory to tempPlayer
                    Territory* won = p->getAdjacentT();
                    cout << "You gained the territory: " << won->getTerritoryName() << endl;
                    won->setPlayerNumber(tempPlayer->getId());
                    tempPlayer->playerTerritories.push_back(won);
                }

            }else if(tempOrder->getType() == "deploy"){
                if(tempOrder->validate()){
                    tempPlayer->removeReinArmy(tempOrder->getArmyCount());
                }
                cout << tempOrder->execute() << '\n';
            }else if(tempOrder->getType() == "blockade"){

                Blockade* p = (Blockade*) tempOrder;

                //give Territory to Neutral Player
                cout << tempOrder->execute() << '\n';
                if(tempOrder->validate()){
                    p->getTarget()->setPlayerNumber(-1);
                    for(int i=0; i< tempPlayer->playerTerritories.size(); i++){
                        if(tempPlayer->playerTerritories.at(i)->getTerritoryNumber() && p->getTarget()->getTerritoryNumber()){
                            tempPlayer->playerTerritories.erase(tempPlayer->playerTerritories.begin()+i);
                        }
                    }
                    cout << "You gave away " << p->getTarget()->getTerritoryName() <<'\n';
                }
            }else if (tempOrder->getType() == "negotiate"){
                Negotiate* p = (Negotiate*) tempOrder;
                //executing and target player cant attack each other for one turn
                if(tempOrder->validate()){
                    friend1 = p->getTargetId();
                    friend2 = tempPlayer->getId();
                    cout << friend1 << " and " << friend2 << " are allies for one turn.\n";
                }
                cout << tempOrder->execute() << '\n';
            }else{
                cout << tempOrder->execute() << '\n';
            }

        }
    }

    cout << "Finished executing all orders! \n" << endl;

    cout << "Please enter an option" << "\n";
    string input;
    cin >> input;
    while (true) {
        if (input == "endturn") {
            cout << "This turn has finished!" << "\n";
            break;
        }
        else if (input == "win") {
            cout << "THIS IS A WIN!" << "\n";
            winnerFound = true;
            break;
        }
        else {
            cout << "Invalid input, please enter a valid option" << "\n";
            cin >> input;
        }
    }
}
bool PlayManager::checkWinner(Player * p){
    int playerID = p->getId();
    bool win = true;

    for(int k = 0; k < loader->getAllTerritories()->size(); k++){
        Territory tempTerritory = loader->getAllTerritories()->at(k);
        if(!tempTerritory.PlayerCheck(playerID)){
            win = false;
            break;
        }
    }

    return win;
}

void PlayManager::wins() {
    cout << "\n";
    cout <<
         "            '._==_==_=_.'\n"
         "            .-\\:      /-.\n"
         "           | (|:.     |) |\n"
         "            '-|:.     |-'\n"
         "              \\::.    /\n"
         "               '::. .'\n"
         "                 ) (\n"
         "               _.' '._\n"
         "              `\"\"\"\"\"\"\"`\n";
    setPms(win);
    s = WIN;
    printPMS();
    cout << "Please enter an option" << "\n";
    string input = cp->getCommand();
    while (!cp->validate(s, input)) {
        cp->lc.back().saveEffect("Error. Nothing happened.");
        input = cp->getCommand();
    }
    if (input == "end") {
        cout << "Ending the game. See you soon!" << "\n";
        cp->lc.back().saveEffect("Ending the game. See you soon!");
        end();
    }
    else if (input == "play") {
        cout << "Want to replay? Restarting the game!" << "\n";
        cp->lc.back().saveEffect("Want to replay? Restarting the game!");
        gs = startup;
        play();
    }
}
void PlayManager::play() {
    cout << "Game is now restarting. Please wait." << "\n\n";
}
void PlayManager::end() {
    isGameOver = true;
}

void StartupManager::transition() {
    Subject::notify(this);
}

void Command::stringToLog() {
    fstream filestream;
    filestream.open("gamelog.txt", ios::app);
    filestream << effect << "\n";
    filestream.close();
};

void CommandProcessor::stringToLog() {
    fstream filestream;
    filestream.open("gamelog.txt", ios::app);
    filestream << "Saving: " << lc.back().toString();
    filestream.close();
};

void StartupManager::stringToLog() {
    fstream filestream;
    filestream.open("gamelog.txt", ios::app);
    filestream << "State: " + smsmap.at(sms) << "\n";
    filestream.close();
};