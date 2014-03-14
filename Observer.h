#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
    public:
        virtual unsigned int getId();
        virtual void notify();
        virtual void setId(unsigned int);
    private:
        unsigned int id;
};

unsigned int Observer::getId()
{
    return id;
}

void Observer::setId(unsigned int m_id)
{
    id = m_id;
}

void Observer::notify()
{
    printf("Notify observer\n");
}
#endif
