#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Player.h"
#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

enum GameState {startup,play};
enum StartupManagerState {start, mapLoaded,mapValidated, playersAdded, finishSMS};
enum PlayManagerState {assignReinforcement, issueOrders, executeOrders, win, finishPMS};
enum State {START, MAPLOADED, MAPVALIDATED, PLAYERADDED, ASSIGNREINFORCEMENT, ISSUEORDER, EXECUTEORDERS, WIN};
enum possibleCommands {loadmap, validatemap, addplayer, gamestart, replay, quit};

extern bool isGameOver;

class Command {
public:
    Command(string c);
    void saveEffect(string e);
    string toString();
private:
    string command;
    string effect;
};

class CommandProcessor{
public:
    string getCommand();
    vector <Command> lc;
    void showList();
    bool validate(State st, string cmd);
private:
    string readCommand();
    void saveCommand(string c);
};

class StartupManager {
    StartupManagerState sms;
    public:
        void printSMS();
        void setSms(StartupManagerState s);
        void init ();
        void mapLoad(string arg);
        void validateMap();
        void addPlayers(string arg);
        void gameStart();
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

#endif