#include <iostream>
#include <map>

using namespace std;

enum GameState {startup,play};
enum StartupManagerState {start, mapLoaded,mapValidated, playersAdded, finishSMS};
enum PlayManagerState {assignReinforcement, issueOrders, executeOrders, win, finishPMS};

extern const map <GameState, string> gsmap;
extern const map <StartupManagerState, string> smsmap;
extern const map <PlayManagerState, string> pmsmap;

extern GameState gs;

extern bool isGameOver;

class StartupManager {
    StartupManagerState sms;
    public:
        void printSMS();
        void setSms(StartupManagerState s);
        void init ();
        void mapLoad();
        void validateMap();
        void addPlayers() ;
        void assignCountries();
};

class PlayManager {
    PlayManagerState pms;
    public:
        void printPMS() ;
        void setPms(PlayManagerState p);
        void init ();
        void issueOrder();
        void endIssueOrders();
        void exeOrder();
        void endExeOrders();
        void wins();
        void play();
        void end();
};

