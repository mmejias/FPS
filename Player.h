//Followed: www.g-truc.net/project-0016.html

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>
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

        void rotateX();
        void rotateY();
        void rotateZ();

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
    rotX = yaw;
    rotY = pitch;
    camera.update(yaw, pitch, position);
    rotateX();
    rotateY();
    //    rotateZ();
    camera.look();

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
    glm::vec4 move = glm::vec4(-m_dist, 0.0f, 0.0f, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);
}

void Player::moveLeft(float m_dist)
{
    
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(m_dist, 0.0f, 0.0f, 1.0f);
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

void Player::rotateX()
{
    rotX /= 180*PI;
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotX, camera.getTarget());
    glm::vec4 move = glm::vec4(rotX, 0.0f, 0.0f, 1.0f);
    glm::vec4 trans = rot*move;
    glm::vec3 m_target = glm::vec3(trans);
    //glm::quat quatYaw = glm::angleAxis(rotX, glm::vec3(0.0f, 1.0f, 0.0f));
    //m_target = quatYaw * m_target;
    camera.setTarget(m_target);
    
}

void Player::rotateY()
{
    rotY /= 180*PI;
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotY, camera.getTarget());
    glm::vec4 move = glm::vec4(rotY, 0.0f, 0.0f, 1.0f);
    glm::vec4 trans = rot*move;
    glm::vec3 m_target = glm::vec3(trans);
    //glm::quat quatYaw = glm::angleAxis(rotY, glm::vec3(0.0f, 0.0f, 1.0f));
    //m_target = quatYaw * m_target;
    camera.setTarget(m_target);
}

void Player::rotateZ()
{
    glm::vec3 m_target = glm::cross(position, camera.getTarget());
    //glm::mat4 rot = glm::
    m_target = glm::normalize(m_target);
    camera.setTarget(m_target);
}

void Player::fire()
{
    Blaster shot;
    shot.position = position;
    
    weapon.push(shot);    
    printf("Weapon fired\n");
}
