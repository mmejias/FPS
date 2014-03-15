#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <GL/glu.h>
#include <cmath>

class Crosshair
{
    public:
        Crosshair(unsigned int, unsigned int);
        void draw();
        void update();
    private:
        unsigned int width; //Window width
        unsigned int height; //Window height
};

Crosshair::Crosshair(unsigned int winWidth, unsigned int winHeight)
{
    width = winWidth;
    height = winHeight;
}

void Crosshair::draw()
{
    float m_width = (float) width;
    float m_height = (float) height;
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(m_width/2, m_height/2-10);
        glVertex2f(m_width/2, m_height/2+10);
        glVertex2f(m_width/2-10, m_height/2);
        glVertex2f(m_width/2+10, m_height/2);
    glEnd();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void Crosshair::update()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
}

#endif
