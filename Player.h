//Followed: www.g-truc.net/project-0016.html
#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>
#include "Blaster.h"
#include "Camera.h"
#include "Subject.h"
#include "Observer.h"
#include "Enemy.h"
#include "Crosshair.h"

class Player : public Subject
{
    public:
        Player();
        ~Player();
        virtual void registerObserver(Enemy);
        virtual void unregisterObserver(Enemy);
        virtual void notifyObservers();
        void notifyObserver(unsigned int);
        
        void fire();
        void moveBackward(float);
        void moveForward(float);
        void moveLeft(float);
        void moveRight(float);

        void rotateX();
        void rotateY();
        void rotateZ();

        void render(float, float);
        glm::vec3 position;
        glm::vec3 view;
        glm::vec3 up;
        float angle;
        float rotX, rotY, rotZ;
    protected:
        Enemy observers[100];
        FPCamera camera;
        Blaster weapon;
        int space;
        unsigned int watchers;   //size of observers array 
};

Player::Player()
{
   space = -1;
   watchers = 0;
   position = glm::vec3(0.0f, 0.0f, -25.0f);
   view = glm::vec3(0.0f, 0.0f, 1.0f);
   up = glm::vec3(0.0f, 1.0f, 0.0f);
    
   angle = 0.0f;
   rotX = rotY = rotZ = 0.0f;

   camera.init(position, glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

Player::~Player()
{
    printf("Delete Player\n");
}

void Player::notifyObservers()
{
    for(unsigned int i = 0; i < watchers; ++i)
    {
        observers[i].notify(this->position);
    }
    
}

void Player::notifyObserver(unsigned int m_id)
{
    if(m_id >= 0 && m_id < watchers)
        observers[m_id].notify(this->position);
}

void Player::registerObserver(Enemy observer)
{
    if(space != -1)
    {
        observer.setId(space);
        observers[space] = observer;
        space = -1;
    }
    else if(watchers < 100)
    {
        observer.setId(watchers);
        observers[watchers] = observer;
        ++watchers;
    }
    else
    {
        printf("Reconsider size of observer array\n");
        printf("Out of bounds\n");
    }
}

void Player::unregisterObserver(Enemy observer)
{
    space = observer.getId();
}

void Player::render(float yaw, float pitch)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, 1.333, 2, 100); 
    rotZ = rotX = yaw;
    rotY = pitch;
    
    weapon.update();
    weapon.draw();
    
    camera.update(yaw, pitch, position);
    camera.look();
    
}

void Player::moveForward(float m_dist)
{
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(camera.getForward().x, 
                               camera.getForward().y, 
                               camera.getForward().z, 
                               1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::moveRight(float m_dist)
{
    glm::vec3 right = -camera.getLeft()*m_dist;
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(right.x, right.y, right.z, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::moveLeft(float m_dist)
{    
    glm::vec3 left = camera.getLeft()*m_dist;
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(left.x, left.y, left.z, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::moveBackward(float m_dist)
{
    
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(-camera.getForward().x, 
                               -camera.getForward().y, 
                               -camera.getForward().z,
                                1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::rotateX()
{
    rotX /= 180*PI;
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotX, camera.getTarget());
    glm::vec4 move = glm::vec4(rotX, 0.0f, 0.0f, 1.0f);
    glm::vec4 trans = rot*move;
    glm::vec3 m_target = glm::vec3(trans);
    camera.setTarget(m_target);
    
}

void Player::rotateY()
{
    rotY /= 180*PI;
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotY, camera.getTarget());
    glm::vec4 move = glm::vec4(0.0f, rotY, 0.0f, 1.0f);
    glm::vec4 trans = rot*move;
    glm::vec3 m_target = glm::vec3(trans);
    camera.setTarget(m_target);
}

void Player::rotateZ()
{
    rotZ /= 180*PI;
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotZ, camera.getTarget());
    glm::vec4 move = glm::vec4(0.0f, 0.0f, rotZ, 1.0f);
    glm::vec4 trans = rot * move;
    glm::vec3 m_target = glm::vec3(trans);
    camera.setTarget(m_target);
}

void Player::fire()
{
    Bullet bullet(camera.getEye(), camera.getTarget());
    weapon.projectiles.push_back(bullet);
}
#endif
