#include "Level.h"
#include "Input.h"
#include "Player.h"
#include "RScreen.h"

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <unistd.h>

void draw();
void initialize();
void render();
void update();
void handleKeys();
void handleMouse();

RScreen rscreen;
Level levelone("LevelOne.obj");
KeyboardHandler keyboard;
MouseHandler mouse;
Player player;
Sphere spheres[5];

int main(int argc, char** argv)
{
    initialize();
    render();

    return 0;
}

void initialize()
{
    float light_position[] = {0.0, 10.0, 1.0, 0.0};
    rscreen.Initialize();
    glViewport(0, 0, rscreen.getWidth(), rscreen.getHeight());
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_position);

    spheres[0].x = -10.0f;  spheres[0].z = -10.0f; 
    spheres[1].x = 10.0f;   spheres[1].z = 10.0f;
    spheres[2].x = 0.0f;    spheres[2].z = 0.0f;
    spheres[3].x = -10.0f; spheres[3].z = 10.0f;
    spheres[4].x = 10.0f; spheres[4].z = -10.0f;
    for(unsigned int i = 0; i < 5; ++i)
        spheres[i].y = 10.0f;
}

void render()
{
   while(1)
   {
        rscreen.Draw();
        switch(rscreen.getEvent().type)
        {
            case Expose:
                draw();
                usleep(500);
                break;
            case KeyPress:
                handleKeys();
                break;
            case MotionNotify:
                handleMouse();
                break;
        }
        draw();
        usleep(500);
   }
}

void draw()
{
    rscreen.View();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //DRAW OTHER OBJECST BETWEEN SCREEN VIEW AND BUFFER
    levelone.draw();
    for(unsigned int i = 0; i < 5; ++i)
        spheres[i].draw();
    player.render(mouse.getdelX(), mouse.getdelY());

    rscreen.Buffer();
}

void handleKeys()
{    
    keyboard.keyDown(rscreen.getEvent());
    if(keyboard.isKeyDown(XK_Up))
    {
        player.moveForward(0.0625);
    }
    if(keyboard.isKeyDown(XK_Escape))
    {
        rscreen.Close();
        exit(0);
    }
}

void handleMouse()
{
    mouse.onMove(rscreen.getEvent());    
}
