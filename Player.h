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
        Blaster weapon;
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
    Bullet bullet(position, camera.getTarget());
    weapon.projectiles.push_back(bullet);
    
    printf("Weapon fired\n");
}
