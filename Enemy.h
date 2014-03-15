#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>
#include "Mathematics/Generator.h"
#include "Observer.h"
#include "Geometry.h"

class Enemy : public Observer
{
    public:
        Enemy();
        glm::vec3 mPosition;
        Sphere mEntity;
        unsigned int getId();
        void notify(glm::vec3);
        void setId(unsigned int);
        void draw();
        void update();
    private:
        unsigned int id;
};


Enemy::Enemy()
{    

}

unsigned int Enemy::getId()
{
    return id;
}

void Enemy::draw()
{
    mEntity.draw();
}

void Enemy::setId(unsigned int m_id)
{
    id = m_id;
}

void Enemy::update()
{

}


void Enemy::notify(glm::vec3 player)
{
    printf("Notify observer\n");
}
#endif
