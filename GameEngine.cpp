#include "GameEngine.h"

using namespace std;

const map <GameState, string> gsmap = {{startup, "startup"}, {play, "play"}};
const map <StartupManagerState, string> smsmap = {{start, "start"}, {mapLoaded, "mapLoaded"}, {mapValidated, "mapValidated"}, {playersAdded, "playersAdded"}, {finishSMS, "finishSMS"}};
const map <PlayManagerState, string> pmsmap = {{assignReinforcement,"assignReinforcement"},{issueOrders, "issueOrders"}, {executeOrders, "executeOrders"}, {win, "win"}, {finishPMS, "finishPMS"}};

bool isGameOver = false;

vector<Player*> listOfPlayers;
// REMEMBER TO ADD DELETE STATEMENT LATER
//---------------------------------------------------------

Map * loader;

GameState gs;

State s;

CommandProcessor cp;

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
    gs = startup;
    setSms(start);
    s = START;
    printSMS();
    cout << "Please enter an option" << "\n";
    string input = cp.getCommand();
    while (!cp.validate(s, input)) {
        cp.lc.back().saveEffect("Error. Nothing happened.");
        input = cp.getCommand();
    }
    string arg = input.substr(input.find(' ') + 1, input.length()-1);
    cout << "Loading the map " + arg << "\n";
    cp.lc.back().saveEffect("Loading the map " + arg);
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
    string input = cp.getCommand();
    while (!cp.validate(s,input) || input.substr(0,input.find(' ')) == "loadmap") {
        if (input == "loadmap") {
            cout << "Loading the map" + arg+ "\n";
            // loadmap
            loader = new Map(arg);
            // loadmap
            cp.lc.back().saveEffect("Loading the map " + arg + "\n");
            printSMS();
            cout << "Please enter an option" << "\n";
        }
        else {
            cp.lc.back().saveEffect("Error. Nothing happened.");
        }
        input = cp.getCommand();
    }
    if (input == "validatemap") {
        cout << "Validating the map." << "\n";
        cp.lc.back().saveEffect("Validating the map.");
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
    string input = cp.getCommand();
    while (!cp.validate(s, input)) {
        cp.lc.back().saveEffect("Error. Nothing happened.");
        input = cp.getCommand();
    }
    string arg = input.substr(input.find(' ') + 1, input.length()-1);
    cout << "Adding player " + arg << "\n";
    cp.lc.back().saveEffect("Adding player " + arg);
    addPlayers(arg);
}
void StartupManager::addPlayers(string arg) {
    cout << "\n";
    // add player
    Player* p = new Player(arg);
    listOfPlayers.push_back(p);
//    Player::addPlayer(p);
    // add player
    setSms(playersAdded);
    s = PLAYERADDED;
    printSMS();
    cout << "Please enter an option" << "\n";
    string input = cp.getCommand();
    cout << input << "\n";
    while (!cp.validate(s, input) || input.substr(0,input.find(' ')) == "addplayer" ) {
        if (input.substr(0,input.find(' ')) == "addplayer") {
            string name = input.substr(input.find(' ') + 1, input.length()-1);
            cout << "Adding player " + name << "\n";
            cp.lc.back().saveEffect("Adding player "+ name);
            // add player
            Player* p2 = new Player(name);      // Avoid overshadowing
            listOfPlayers.push_back(p2);
//            Player::addPlayer(p);
            //
            printSMS();
            cout << "Please enter an option" << "\n";
        }
        else {
            cp.lc.back().saveEffect("Error. Nothing happened.");
        }
        input = cp.getCommand();
    }
    cout << "Assigning countries" << "\n";
    cp.lc.back().saveEffect("Assigning countries");
    cp.showList();
    gameStart();
}
void StartupManager::gameStart() {
    cout << "\n";
    // assign countries
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

// Reinforcement phase
void PlayManager::init () {
    setPms(assignReinforcement);
    s = ASSIGNREINFORCEMENT;
    printPMS();

    // Reinforcement phase starts
    for(int i = 0; i < listOfPlayers.size(); i++){
        // Avoid null pointer issues
        if(listOfPlayers.at(i) == nullptr){continue;}

        Player temp =  *listOfPlayers.at(i);
        int reinArmyNum = (int) ((temp).playerTerritories.size() / 3);

        // Make sure that each player receive minimum 3 reinforcement armies
        if(reinArmyNum <= 3){
            reinArmyNum = 3;
        }
        temp.addReinArmy(reinArmyNum);

        // Consider continent quirk
        //----------------------------------------------

        cout << "DEBUG: " << temp.getPlayerName() << " has " << temp.getReinArmy() << " armies in the reinforcement pool." << endl;
    }

    // Reinforcement phase is done, move on to the next phase on command
    issueOrder();

    // Old code
//    cout << "Please enter an option" << "\n";
//    string input;
//    cin >> input;
//    while (true) {
//        if (input == "issueorder") {
//            cout << "Issuing order." << "\n";
//            issueOrder();
//            break;
//        }
//        else {
//            cout << "Invalid input, please enter a valid option" << "\n";
//            cin >> input;
//        }
//    }
    // ----------------------------------------
}

// Issuing order phase
void PlayManager::issueOrder(){
    cout << "\n";
    // Start issue order phase, print out the current game state
    setPms(issueOrders);
    s = ISSUEORDER;
    printPMS();

    // Debug-------------------------------------------------------
//    cout << "Current size of list of players: " << listOfPlayers.size() << endl;
//    for(int i = 0; i < listOfPlayers.size(); i++){
//        cout << listOfPlayers.at(i) << endl;
//    }
//    cout << endl;
    //-----------------------------------------------------------------

    // Ask user to issue order
    for(int i = 0; i < listOfPlayers.size(); i++){
        // Prevent NULL pointer issue
        if(listOfPlayers.at(i) == nullptr){continue;}
//        cout << "DEBUG: Checked for null pointer \n" << endl;
//        cout << "DEBUG: listOfPlayers element address: " << listOfPlayers.at(i) << endl;

        Player tempPlayer = *listOfPlayers.at(i);
//        cout << "DEBUG: Extracted Player" << tempPlayer << endl;

        bool endIssueOrder = false;

        // Print out user's name and ask to issue order
        cout << "Player " << tempPlayer.getPlayerName() << ", it is your turn to issue order." << endl;
        cout << "DEBUG: " << tempPlayer.getPlayerName() << " has " << tempPlayer.getReinArmy() << " armies in the reinforcement pool." << endl;

        // Loop constantly until the current player has finished issuing order
        while(!endIssueOrder) {
            string input;

            // Check if player has reinforcement army
            // Might have issues with territory to defend vector
            if(tempPlayer.getReinArmy() > 0) {
                cout << "You still have armies in the reinforcement pool, please deploy before you can issue any other order!" << endl;

                // Print out territories that player can deploy army
                cout << "These are the territories that you can deploy to: " << endl;
                vector<Territory *> territoryToDefend = tempPlayer.toDefend();
                for (int k = 0; k < territoryToDefend.size(); k++) {
                    cout << territoryToDefend[k] << endl;
                }

                // Check for valid order
                while (true){
                    // Fetch order from the player
                    cout << "Please enter an order: ";
                    cin >> input;
                    cout << "\n" << endl;

                    if(input == "deploy"){
                        Deploy deployOrder;
                        deployOrder.execute();
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

            // Fetch order from the player
            cout << "Please enter an order: ";
            cin >> input;
            cout << "\n" << endl;

            // Create a new order and check if it is valid
            Order* newOrder = new Order(input);
            if (!(*newOrder).validate()) {
                cout << "Invalid order! Please try again!" << endl;
                continue;
            }
//            cout << "DEBUG: Order address: " << newOrder << endl;

            // Once validated, issue order
            tempPlayer.issueOrder(*newOrder);

            // Ask player if they want to continue issuing order
            cout << "Order issued" << "\n";

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

        cout << "Looping over again" << endl;
    }
//
    endIssueOrders();
    // Old code------------------------------------------------------------
//    cout << "Please enter an option" << "\n";
//    string input;
//    cin >> input;
//    while (true) {
//        if (input == "issueorder") {
//            cout << "Issuing order." << "\n";
//            // issue orders
//            printPMS();
//            cout << "Please enter an option" << "\n";
//            cin >> input;
//        }
//        else if (input == "endissueorders") {
//            cout << "Ending issue orders." << "\n";
//            endIssueOrders();
//            break;
//        }
//        else {
//            cout << "Invalid input, please enter a valid option" << "\n";
//            cin >> input;
//        }
//    }
    // --------------------------------------------------------------------
}

void PlayManager::endIssueOrders() {
    cout << "\n";
    // end issue order
    setPms(executeOrders);
    s = EXECUTEORDERS;
    printPMS();
    cout << "Please enter an option" << "\n";
    string input;
    cin >> input;
    while (true) {
        if (input == "execorder") {
            cout << "Executing order." << "\n";
            exeOrder();
            break;
        }
        else if (input == "endexecorders") {
            cout << "Ending executing orders." << "\n";
            endExeOrders();
            break;
        }
        else if (input == "win") {
            cout << "THIS IS A WIN!" << "\n";
            wins();
            break;
        }
        else {
            cout << "Invalid input, please enter a valid option" << "\n";
            cin >> input;
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

    // Old Code-----------------------------------------------------------
    cout << "Please enter an option" << "\n";
    string input;
    cin >> input;
    while (true) {
        if (input == "execorder") {
            cout << "Executing order." << "\n";
            // execute order
            printPMS();
            cout << "Please enter an option" << "\n";
            cin >> input;
        }
        else if (input == "endexecorders") {
            cout << "Ending executing orders." << "\n";
            endExeOrders();
            break;
        }
        else if (input == "win") {
            cout << "THIS IS A WIN!" << "\n";
            wins();
            break;
        }
        else {
            cout << "Invalid input, please enter a valid option" << "\n";
            cin >> input;
        }
    }
    //------------------------------------------------------------------------
}
void PlayManager::endExeOrders(){
    cout << "\n";
    // end execute orders
    setPms(assignReinforcement);
    s = ASSIGNREINFORCEMENT;
    init();
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
    string input = cp.getCommand();
    while (cp.validate(s, input)) {
        input = cp.getCommand();
    }
    if (input == "end") {
        cout << "Ending the game. See you soon!" << "\n";
        end();
    }
    else if (input == "play") {
        cout << "Want to replay? Restarting the game!" << "\n";
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
