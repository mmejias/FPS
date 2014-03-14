#include "Mathematics/Generator.h"
#include "Player.h"
#include "Observer.h"
#include "Geometry.h"

class Enemy
{
    public:
        Enemy();
        glm::vec3 mPosition;
        Sphere mEntity;
        void draw();
        void update();
    private:
};


Enemy::Enemy()
{    
}

void Enemy::draw()
{
    mEntity.draw();
}

void Enemy::update()
{

}
