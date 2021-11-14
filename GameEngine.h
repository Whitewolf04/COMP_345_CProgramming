#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#pragma once
#include "Player.h"
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <stdlib.h>

using namespace std;

enum GameState {startup,play};
enum StartupManagerState {start, mapLoaded,mapValidated, playersAdded, finishSMS};
enum PlayManagerState {assignReinforcement, issueOrders, executeOrders, win, finishPMS};
enum State {START, MAPLOADED, MAPVALIDATED, PLAYERADDED, ASSIGNREINFORCEMENT, ISSUEORDER, EXECUTEORDERS, WIN};
enum possibleCommands {loadmap, validatemap, addplayer, gamestart, replay, quit};

extern bool isGameOver;

class Command: public Iloggable, Subject{
public:
    Command(string c);
    void saveEffect(string e);
    string toString();
    void stringToLog();
private:
    string command;
    string effect;
};

class CommandProcessor : public Iloggable, Subject{
public:
    string getCommand();
    vector <Command> lc;
    void showList();
    bool validate(State st, string cmd);
    void stringToLog();
private:
    string readCommand();
    void saveCommand(string c);
};

class StartupManager : public Iloggable, Subject {
    StartupManagerState sms;
    public:
        void transition();
        void printSMS();
        void setSms(StartupManagerState s);
        void init ();
        void mapLoad(string arg);
        void validateMap();
        void addPlayers(string arg);
        void gameStart();
        void stringToLog();
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