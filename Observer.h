#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdio.h>
#include <glm/glm.hpp>

class Observer
{
    public:
        virtual unsigned int getId();
        virtual void notify(glm::vec3);
        virtual void setId(unsigned int);
    private:
        unsigned int id;
};

void Observer::notify(glm::vec3 pos)
{

}

unsigned int Observer::getId()
{
    return id;
}

void Observer::setId(unsigned int m_id)
{
    id = m_id;
}


#endif
