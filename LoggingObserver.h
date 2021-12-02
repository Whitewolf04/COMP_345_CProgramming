#pragma once

//User Defined Classes
class Iloggable {
public:
    //Subject Observer related methods
    virtual void stringToLog() = 0;
};

class Subject {
public:
    //Constructors
    Subject();
    Subject(const Subject &s);
    Subject& operator =(const Subject& o);
    //Subject Observer related methods
    void notify(Iloggable* s);
};


class Observer {
public:
    //Subject Observer related methods
    virtual void Update(Iloggable& s) = 0;
};


class LogObserver : Observer {
public:
    //Constructors
    LogObserver();
    LogObserver(const LogObserver& s);
    LogObserver& operator =(const LogObserver& o);
    //Subject Observer related methods
    static void Update(Iloggable* s);
};