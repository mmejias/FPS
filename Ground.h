#ifndef GROUND_H
#define GROUND_H

#include <GL/gl.h>
#include <GL/glu.h>

class Ground
{
    public:
        Ground();
        ~Ground();
        float* getBoundaries();
        void draw();
    private:
        float* boundaries;

};

Ground::Ground()
{
    boundaries = new float[2];
    boundaries[0] = -100.0f;
    boundaries[1] = 100.0f;
}

Ground::~Ground()
{
    delete[] boundaries;
}

float* Ground::getBoundaries()
{
    return boundaries;
}

void Ground::draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(boundaries[0], 0.0f, boundaries[0]);
        glVertex3f(boundaries[0], 0.0f, boundaries[1]);
        glVertex3f(boundaries[1], 0.0f, boundaries[1]);
        glVertex3f(boundaries[1], 0.0f, boundaries[0]);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}


#endif
