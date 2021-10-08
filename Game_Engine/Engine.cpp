#include <iostream>

using namespace std;

enum GameState {start,play};
enum StartupManagerState {starts, mapLoaded,mapValidated, playersAdded, finishSMS};
enum PlayManagerState {assignReinforcement, issueOrders, executeOrders, win, finishPMS};

GameState gs;

class StartupManager {
    StartupManagerState sms;
public:
    void setSms(StartupManagerState s) {
        sms = s;
    }
    void init () {
        gs = start;
        setSms(starts);
        mapLoad();
    }
    void mapLoad() {

        cout << "Loading the map.\n";
        setSms(mapLoaded);
        validateMap();
    }
    void validateMap() {

        cout << "Validating the map.\n";
        setSms(mapValidated);
        addPlayers();
    }
    void addPlayers() {

        cout << "Adding players.\n";
        setSms(playersAdded);
        assignCountries();
    }
    void assignCountries() {

        cout << "Assigning countries.\n";
        setSms(finishSMS);
        gs = play;
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