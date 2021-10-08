#include <iostream>
#include <map>

using namespace std;

enum GameState {start,play};
enum StartupManagerState {starts, mapLoaded,mapValidated, playersAdded, finishSMS};
enum PlayManagerState {assignReinforcement, issueOrders, executeOrders, win, finishPMS};

map <GameState, string> gsmap = {{start,"start"},{play, "play"}};
map <StartupManagerState, string> smsmap = {{starts,"starts"},{mapLoaded, "mapLoaded"}, {mapValidated, "mapValidated"}, {playersAdded, "playersAdded"}, {finishSMS, "finishSMS"}};
map <PlayManagerState, string> pmsmap = {{assignReinforcement,"assignReinforcement"},{issueOrders, "issueOrders"}, {executeOrders, "executeOrders"}, {win, "win"}, {finishPMS, "finishPMS"}};


GameState gs;

class StartupManager {
    StartupManagerState sms;
    public:
        void printSMS() {
            cout << "The game is in " << gsmap.at(gs) << " state at the " << smsmap.at(sms) << " sub-state." << "\n";
        }
        void setSms(StartupManagerState s) {
            sms = s;
        }
        void init () {
            gs = start;
            setSms(starts);
            printSMS();
            cout << "Please enter an option" << "\n";
            string input;
            cin >> input;
            while (true) {
                if (input == "loadmap") {
                    cout << "Loading the map.\n";
                    mapLoad();
                    break;
                }
                else {
                    cout << "Invalid input, please enter a valid option" << "\n";
                    cin >> input;
                }
            }
        }
        void mapLoad() {
            // load map
            setSms(mapLoaded);
            printSMS();
            cout << "Please enter an option" << "\n";
            string input;
            cin >> input;
            while (true) {
                if (input == "loadmap") {
                    cout << "Loading the map.\n";
                    printSMS();
                    cout << "Please enter an option" << "\n";
                    cin >> input;
                    // load map
                }
                else if (input == "validatemap") {
                    cout << "Validating the map." << "\n";
                    validateMap();
                    break;
                }
                else {
                    cout << "Invalid input, please enter a valid option" << "\n";
                    cin >> input;
                }
            }
        }
        void validateMap() {
            // validate map
            setSms(mapValidated);
            printSMS();
            cout << "Please enter an option" << "\n";
            string input;
            cin >> input;
            while (true) {
                if (input == "addplayer") {
                    cout << "Adding player." << "\n";
                    addPlayers();
                    break;
                }
                else {
                    cout << "Invalid input, please enter a valid option" << "\n";
                    cin >> input;
                }
            }
        }
        void addPlayers() {
            // load map
            setSms(playersAdded);
            printSMS();
            cout << "Please enter an option" << "\n";
            string input;
            cin >> input;
            while (true) {
                if (input == "addplayer") {
                    cout << "Adding player." << "\n";
                    printSMS();
                    cout << "Please enter an option" << "\n";
                    cin >> input;
                    // load map
                }
                else if (input == "assigncountries") {
                    cout << "Assigning countries" << "\n";
                    validateMap();
                    break;
                }
                else {
                    cout << "Invalid input, please enter a valid option" << "\n";
                    cin >> input;
                }
            }
            assignCountries();
        }
        void assignCountries() {
            // assign countries
            setSms(finishSMS);
            gs = play;
            cout << "End of startup phase." << "\n";
            cout << "Thank you for your patience. The game shall now start!\n";
        }

};

class PlayManager {
    PlayManagerState pms;
    public:
        void setPms(PlayManagerState p) {
            pms = p;
        }
        void init () {
            setPms(assignReinforcement);
            issueOrder();
        }
        void issueOrder(){

            setPms(issueOrders);
            endIssueOrders();

        }
        void endIssueOrders() {

            setPms(executeOrders);
            exeOrder();
        }
        void exeOrder() {

        }
        void endExeOrders(){

            setPms(assignReinforcement);
            issueOrder();
        }
        void wins() {

        }
        void play() {

        }
        void end() {

        }

};

int main() {
    cout << "Welcome to Warzone!" << "\n";
    cout << "The game will now start setting up, please wait." << "\n";
    StartupManager sm;
    sm.init();
    PlayManager pm;
    pm.init();

    return 0;
}
