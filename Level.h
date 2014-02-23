#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>


class Level
{
    public:
        Level();
        ~Level(); 
        void draw();
        void update();
    private:
        float* vertices;
        
};

Level::Level()
{
    vertices = new float[4];
}

Level::~Level()
{
    delete [] vertices;
}

void Level::draw()
{
    glClear( GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0, 0, 1);
        glVertex3f(1, 0, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(0, 1, 0);
    glEnd();
}
