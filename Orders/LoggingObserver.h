#ifndef CLION_LOGGINGOBSERVER_H
#define CLION_LOGGINGOBSERVER_H

class Iloggable {
public:
    virtual void stringToLog() = 0;
};

class Subject {
public:
    void notify(Iloggable* s);
};


class Observer {
public:
    virtual void Update(Iloggable& s) = 0;
};


class LogObserver : Observer {
public:
    static void Update(Iloggable* s);
};


/*
1-Implementez les classe en haut dans un duo LoggingObserver cpp/h
2-Pour toute ces methods:
CommandProcessor::saveCommand(), Order::execute(), Command::saveEffect(),
OrderList::addOrder(), and GameEngine::transition()
-Chaque classe doit inherit de Iloggable et Subject
-Dans chaque method mettez : Subject::notify(*this); a la fin de la method
-ajouter cette method a vos classe :
void stringToLog() {
        fstream filestream;
        filestream.open("gamelog.txt", ios::app);
        //Code specific parts here
        filestream.close();
    };
    */

#endif //CLION_LOGGINGOBSERVER_H
