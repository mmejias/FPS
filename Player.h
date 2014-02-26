#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "FPVector.h"

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

        void render();
    protected:
        glm::vec3 position;
        glm::vec3 view;
        glm::vec3 right;
        glm::vec3 up;
        float angle;
        float rotX, rotY, rotZ;
       // List blasters;
};

Player::Player()
{
   view = glm::vec3(0.0, 0.0, 1.0);
   right = glm::vec3(1.0, 0.0, 0.0);
   up = glm::vec3(0.0, 1.0, 0.0);

   angle = 0.0;
   rotX = rotY = rotZ = 0.0;
}

Player::~Player()
{
    printf("Delete Player\n");
}

void Player::render()
{
    //FPVector3 perspective = position+view;
/*
    gluLookAt( position.x, position.y, position.z,
               view.x, view.y, view.z,
               up.x, up.y, up.z );
*/

    gluLookAt(0.0f, 0.0f, 0.0f, 
              0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 1.0f);

}

void Player::moveForward(float m_dist)
{
    float dist = 0.0;
    position.z = position.z + m_dist;
    view.z = view.z + m_dist;
    /*
     * dist = position.getZ();
    dist = dist + m_dist;
    position.setZ(dist);
    
    dist = view.getZ();
    dist = dist + m_dist;
    view.setZ(dist);
    */
}

void Player::rotateX(float m_angle)
{
   //Depending on Mouse Motion rotate in X
   //Rotation matrix
   /*
   position.setX(cos(m_angle));
   position.setY(sin(m_angle));
   view.setX(-sin(m_angle));
   view.setY(cos(m_angle));
    */
}
