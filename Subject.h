#ifndef SUBJECT_H
#define SUBJECT_H

#include <stdio.h>
#include "Observer.h"

class Subject
{
    public:
        virtual void registerObserver(Observer);
        virtual void unregisterObserver(Observer);
        virtual void notifyObservers();
};

void Subject::registerObserver(Observer o)
{
    
}

void Subject::unregisterObserver(Observer o)
{

}

void Subject::notifyObservers()
{

}

#endif
