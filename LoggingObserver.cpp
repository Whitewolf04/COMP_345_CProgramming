#include "LoggingObserver.h"

void Subject::notify(Iloggable* s) {
    LogObserver::Update(s);
}

void LogObserver::Update(Iloggable* s) {
    s->stringToLog();
}