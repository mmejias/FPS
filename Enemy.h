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
        bool onPatrol;
        unsigned int id;
        unsigned int point, pos;    //Patrol point and path position, respectively
        Level* map;
        std::vector<glm::vec3> path;
        std::vector<glm::vec3> patrol;
};


Enemy::Enemy()
{    
    onPatrol = true;
    hasPath = false;
    position.y = 1.0f;
    mEntity.y = position.y;
    mEntity.setRadius(2.5f);    
    point = 0;
    pos = 0;
    //Set up a patrol region for Enemy
    constructPatrol(patrol, position);
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
    
    if(onPatrol)
    { 
        if(point >= patrol.size())
            point = 0;
        glm::vec4 move = glm::vec4(patrol[point].x,
                                   0.0f,
                                   patrol[point].z,
                                   1.0f);
        glm::vec4 transformed = trans * move;
        position = glm::vec3(transformed);
        ++point;
    }
    if(hasPath)
    {
        glm::vec4 move = glm::vec4(path[pos].x,
                                   path[pos].y,
                                   path[pos].z,
                                   1.0f);
        glm::vec4 transformed = trans * move;
        position = glm::vec3(transformed);

        ++pos;
        if(pos >= path.size())
        {
            patrol.clear();
            constructPatrol(patrol, position);
            hasPath = false;
        }
    }

    mEntity.x = position.x;
    mEntity.y = position.y; 
    mEntity.z = position.z;
}

void Enemy::notify(glm::vec3 player)
{
    printf("Notify observer\n");
    patrol.clear();
    path.clear();
    findPath(path, player, position, map);
    //Set State to Alert

    hasPath = true;
}

#endif
