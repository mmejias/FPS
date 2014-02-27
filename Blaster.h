#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Blaster
{
    //Draw some blaster-esque firing device
    public:
        Blaster();
        glm::vec3 position, velocity;
        bool visible;
        void draw();
        void update(float);
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
    glBegin(GL_TRIANGLES);
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x+1.0f, position.y, position.z);
        glVertex3f(position.x+0.5f, position.y+1.0f, position.z);
    glEnd();
}

void Blaster::update(float dt)
{ 
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    glm::vec4 move = glm::vec4(0.0f, 0.0f, dt, 1.0f);
    glm::vec4 transformed = trans * move;
    position = glm::vec3(transformed);

    ++counter;

    if(counter > 10000)
     {
         visible = false;
     }
}
