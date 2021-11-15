#include "LoggingObserver.h"

//Default Constructors definitions
Subject::Subject() {}
LogObserver::LogObserver() {}
//Copy Constructors definitions
Subject::Subject(const Subject& s) {}
LogObserver::LogObserver(const LogObserver& s) {}
//Assignemnt Operators definitons
Subject& Subject::operator =(const Subject& o) {
    return *this;
}
LogObserver& LogObserver::operator =(const LogObserver& o) {
    return *this;
}

//StringToLog function which will be inhetired by ConcreteSubjects
void Subject::notify(Iloggable* s) {
    LogObserver::Update(s);
}
//Update Function which will call stringToLog for each subject
void LogObserver::Update(Iloggable* s) {
    s->stringToLog();
}