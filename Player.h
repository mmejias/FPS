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
   view.setZ(-1.0);
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

    gluLookAt( position.getX(), position.getY(), position.getZ(),
               perspective.getX(), perspective.getY(), perspective.getZ(),
               up.getX(), up.getY(), up.getZ() );
}
