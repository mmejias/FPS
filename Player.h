//Followed: www.g-truc.net/project-0016.html

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>
//#include "FPVector.h"
#include "Blaster.h"
#include "Camera.h"


class Player
{
    public:
        Player();
        ~Player();
        void fire();
        void moveBackward(float);
        void moveForward(float);
        void moveLeft(float);
        void moveRight(float);

        void rotateX(float);
        void rotateY(float);
        void rotateZ(float);

        void render(float, float);
    //protected:
        glm::vec3 position;
        glm::vec3 view;
        glm::vec3 up;
        float angle;
        float rotX, rotY, rotZ;
    protected:
        FPCamera camera;
        std::queue<Blaster> weapon;
};

Player::Player()
{
   position = glm::vec3(0.0f, 0.0f, 0.0f);
   view = glm::vec3(0.0f, 0.0f, 1.0f);
   up = glm::vec3(0.0f, 1.0f, 0.0f);

   angle = 0.0f;
   rotX = rotY = rotZ = 0.0f;

   camera.init(position, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
   //camera.init(position, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Player::~Player()
{
    printf("Delete Player\n");
}

void Player::render(float yaw, float pitch)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, 1.333, 2, 100); 
    camera.update(yaw, pitch, position);

    if(!weapon.empty())
    {
        weapon.front().update(0.03125f);
        if(!weapon.front().visible)
            weapon.pop();
    }


}

void Player::moveForward(float m_dist)
{
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(0.0f, 0.0f, m_dist, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::moveRight(float m_dist)
{
    
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(m_dist, 0.0f, 0.0f, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::moveLeft(float m_dist)
{
    
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(-m_dist, 0.0f, 0.0f, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::moveBackward(float m_dist)
{
    
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(0.0f, 0.0f, -m_dist, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::rotateX(float m_angle)
{
   //Depending on Mouse Motion rotate in X
     glm::mat4 rot = glm::rotate(glm::mat4(1.0f), m_angle, position);
     glm::vec4 move = glm::vec4(m_angle, 0.0f, 0.0f, 1.0f);
     glm::vec4 transformed = rot*move;
     position = glm::vec3(transformed); 
}

void Player::fire()
{
    Blaster shot;
    shot.position = position;
    
    weapon.push(shot);    
    printf("Weapon fired\n");
}
