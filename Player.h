#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
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
        FPVector3 position;
        FPVector3 view;
        FPVector3 right;
        FPVector3 up;
        float angle;
        float rotX, rotY, rotZ;
       // List blasters;
};

Player::Player()
{
   view.setZ(1.0);
   right.setX(1.0);
   up.setY(1.0);

   angle = 0.0;
   rotX = rotY = rotZ = 0.0;
}

Player::~Player()
{
    printf("Delete Player\n");
}

void Player::render()
{
    FPVector3 perspective = position+view;
/*
    gluLookAt( position.getX(), position.getY(), position.getZ(),
               view.getX(), view.getY(), view.getZ(),
               up.getX(), up.getY(), up.getZ() );
*/

    gluLookAt(0.0f, 0.0f, 0.0f, 
              0.0f, 0.0f, 1.0f,
              0.0f, 1.0f, 0.0f);

}

void Player::moveForward(float m_dist)
{
    float dist = 0.0;
    dist = position.getZ();
    dist = dist + m_dist;
    position.setZ(dist);
    
    dist = view.getZ();
    dist = dist + m_dist;
    view.setZ(dist);
}

void Player::rotateX(float m_angle)
{
   //Depending on Mouse Motion rotate in X
   //Rotation matrix
   position.setX(cos(m_angle));
   position.setY(sin(m_angle));
   view.setX(-sin(m_angle));
   view.setY(cos(m_angle));
}
