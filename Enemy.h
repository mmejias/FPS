#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stdlib.h>
#include "Mathematics/Generator.h"
#include "Pathfinding/Pathfinding.h"
#include "Observer.h"
#include "Geometry.h"
#include "Level.h"

class Enemy : public Observer
{
    public:
        Enemy();
        ~Enemy();
        glm::vec3 position;
        Sphere mEntity;
        unsigned int getId();
        bool pathExists();
        void notify(glm::vec3);
        void setId(unsigned int);
        void setMap(Level*);
        void draw();
        void update();
    private:
        bool hasPath;
        unsigned int id;
        std::vector<glm::vec3> path;
        std::vector<glm::vec3> patrol;
        Level* map;
};


Enemy::Enemy()
{    
    hasPath = false;
    position.y = 1.0f;
    mEntity.y = position.y;
    mEntity.setRadius(2.5f);    

    //Set up a patrol region for Enemy
    //constructPatrol(patrol, position);
}

Enemy::~Enemy()
{
    delete map;
}

unsigned int Enemy::getId()
{
    return id;
}

bool Enemy::pathExists()
{
    return hasPath;
}

void Enemy::setMap(Level* m_map)
{
    map = m_map;
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
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);

    mEntity.x = position.x;
    mEntity.y = position.y;
    mEntity.z = position.z;
}

void Enemy::notify(glm::vec3 player)
{
    printf("Notify observer\n");
    
    path.clear();
    findPath(path, player, position, map);
    //Set State to Alert

    hasPath = true;
}

#endif
