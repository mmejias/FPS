#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "FPVector.h"
#include "Camera.h"

class Blaster
{
    //Draw some blaster-esque firing device
    public:
        void draw();
        void update();
};

struct Node
{
    Node* next;
    Blaster info;
};

class List
{
    //You should have a container to fire your blaster
    public:
        List();
        void insert(Blaster);
        void deleteItem(Blaster);
    private:
        Node root;
};

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
/*
    gluLookAt( position.x, position.y, position.z,
               view.x, view.y, view.z,
               up.x, up.y, up.z );
*/
/*
    gluLookAt(0.0f, 0.0f, 0.0f, 
              0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 1.0f);
*/
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
   
}
