#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Geometry.h"

#ifndef BLASTER_H
#define BLASTER_H

class Bullet
{
    public:
        Bullet();
        Bullet(glm::vec3, glm::vec3);
        glm::vec3 position, direction;
        bool getVisibility();
        void draw();
        void update();
    private: 
        bool onScreen;
        unsigned int timer;
};

Bullet::Bullet()
{
    onScreen = true;
    timer = 0;
}

Bullet::Bullet(glm::vec3 m_pos, glm::vec3 m_dir)
{
    position = m_pos;
    direction = glm::normalize(m_dir);
    onScreen = true;
    timer = 0;
}

bool Bullet::getVisibility()
{
    return onScreen;
}

void Bullet::draw()
{
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(position.x,      position.y,      position.z);
        glVertex3f(position.x+1.0f, position.y,      position.z+1.0f);
        glVertex3f(position.x+1.0f,  position.y+1.0f, position.z+1.0f);
    glEnd();
}

void Bullet::update()
{
    
    ++timer;
    if(timer > 100000000)
        onScreen = false;
/*
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(direction.x, direction.y, direction.z, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
*/
}

class Blaster
{
    //Draw some blaster-esque firing device
    public:
        Blaster();
        std::vector<Bullet> projectiles;
        bool visible;
        void draw();
        void update();
    protected:
        int counter;
};

Blaster::Blaster()
{
    counter = 0;
    visible = true;
}

void Blaster::draw()
{
    for(unsigned int i = 0; i < projectiles.size(); ++i)
        projectiles[i].draw();
}

bool isVisible(Bullet b)
{
    if(b.getVisibility())
        return true;
    else 
        return false;
}

void Blaster::update()
{ 
   for(unsigned int i = 0; i < projectiles.size(); ++i)
   {
       projectiles[i].update(); 
   }

//   if(!projectiles.empty())   
//   projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), isVisible));
   
}
#endif
