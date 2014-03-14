#include "Observer.h"

#ifndef SUBJECT_H
#define SUBJECT_H

class Subject
{
    public:
        virtual void registerObserver(Observer) = 0;
        virtual void unregisterObserver(Observer) = 0;
        virtual void notifyObservers() = 0;
    private:
        Observer observers[100];
};

#endif
