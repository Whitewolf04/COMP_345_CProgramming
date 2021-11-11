#include "GameEngine.h"

using namespace std;

const map <GameState, string> gsmap = {{startup, "startup"}, {play, "play"}};
const map <StartupManagerState, string> smsmap = {{start, "start"}, {mapLoaded, "mapLoaded"}, {mapValidated, "mapValidated"}, {playersAdded, "playersAdded"}, {finishSMS, "finishSMS"}};
const map <PlayManagerState, string> pmsmap = {{assignReinforcement,"assignReinforcement"},{issueOrders, "issueOrders"}, {executeOrders, "executeOrders"}, {win, "win"}, {finishPMS, "finishPMS"}};

bool isGameOver = false;

vector<Player*> listOfPlayers;

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
    Player p(arg);
    listOfPlayers.push_back(&p);
    // add player
    setSms(playersAdded);
    s = PLAYERADDED;
    printSMS();
    cout << "Please enter an option" << "\n";
    string input = cp.getCommand();
    cout << input << "\n";
    while (!cp.validate(s, input) || input.substr(0,input.find(' ')) == "addplayer" ) {
        if (input.substr(0,input.find(' ')) == "addplayer") {
            cout << "Adding player " + input.substr(input.find(' ') + 1, input.length()-1) << "\n";
            cp.lc.back().saveEffect("Adding player "+ input.substr(input.find(' ') + 1, input.length()-1));
            // add player
            Player p(arg);
            listOfPlayers.push_back(&p);
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
        Player temp = *listOfPlayers.at(i);
        int reinArmyNum = (int) (temp.playerTerritories.size()/3);
        temp.addReinArmy(reinArmyNum);

        // Consider continent quirk
        //----------------------------------------------
    }

    // Reinforcement phase is done, move on to the next phase on command
    cout << "Please enter an option" << "\n";
    string input;
    cin >> input;
    while (true) {
        if (input == "issueorder") {
            cout << "Issuing order." << "\n";
            issueOrder();
            break;
        }
        else {
            cout << "Invalid input, please enter a valid option" << "\n";
            cin >> input;
        }
    }
}

// Issuing order phase
void PlayManager::issueOrder(){
    cout << "\n";
    // issue orders
    setPms(issueOrders);
    s = ISSUEORDER;
    printPMS();
    cout << "Please enter an option" << "\n";
    string input;
    cin >> input;
    while (true) {
        if (input == "issueorder") {
            cout << "Issuing order." << "\n";
            // issue orders
            printPMS();
            cout << "Please enter an option" << "\n";
            cin >> input;
        }
        else if (input == "endissueorders") {
            cout << "Ending issue orders." << "\n";
            endIssueOrders();
            break;
        }
        else {
            cout << "Invalid input, please enter a valid option" << "\n";
            cin >> input;
        }
    }
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
