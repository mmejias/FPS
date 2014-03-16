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
        void notify(glm::vec3);
        void setId(unsigned int);
        void setMap(Level*);
        void draw();
        void update();
    private:
        bool hasPath;
        unsigned int id;
        std::vector<glm::vec3> path;
        Level* map;
};


Enemy::Enemy()
{    
    hasPath = false;
    position.y = 1.0f;
    mEntity.y = position.y;
    mEntity.setRadius(2.5f);    
}

Enemy::~Enemy()
{
    delete map;
}

unsigned int Enemy::getId()
{
    return id;
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
    mEntity.x = position.x;
    mEntity.z = position.z;

    if(hasPath && !path.empty())
    {
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
        glm::vec4 move = glm::vec4(path[path.size()-1].x,
                                   path[path.size()-1].y,
                                   path[path.size()-1].z,
                                   1.0f);
        glm::vec4 transformed = trans * move;
        position = glm::vec3(transformed);
        path.pop_back();
    }
}


void Enemy::notify(glm::vec3 player)
{
    printf("Notify observer\n");
    //A* Star search
    findPath(path, player, position, map); 
    hasPath = true;
}
#endif
