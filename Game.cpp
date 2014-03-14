#include "Level.h"
#include "Input.h"
#include "Player.h"
#include "RScreen.h"
#include "Enemy.h"

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
void release();
void handleKeys();
void handleMouse();
void lighting();

RScreen rscreen;
Level levelone("LevelOne.obj");
KeyboardHandler keyboard;
MouseHandler mouse(rscreen.getWidth(), rscreen.getHeight());
Player player;
Sphere spheres[5];
Enemy opposition;

int main(int argc, char** argv)
{
    initialize();
    render();

    return 0;
}

void initialize()
{
    static Cursor cursor;
    rscreen.Initialize();
    
    //Grab Pointer
    XGrabPointer(rscreen.getDisplay(),
                 rscreen.getWindow(),
                 False,
                 EnterWindowMask | LeaveWindowMask | PointerMotionMask,
                 GrabModeAsync,
                 GrabModeAsync,
                 rscreen.getWindow(),
                 cursor,
                 CurrentTime);
    
    XGrabKeyboard(rscreen.getDisplay(),
                  rscreen.getWindow(),
                  False,
                  GrabModeAsync,
                  GrabModeAsync,
                  CurrentTime);    


    glViewport(0, 0, rscreen.getWidth(), rscreen.getHeight());
     
    lighting();
    
    /*
    spheres[0].x = -10.0f;  spheres[0].z = -10.0f; 
    spheres[1].x = 10.0f;   spheres[1].z = 10.0f;
    spheres[2].x = 0.0f;    spheres[2].z = 0.0f;
    spheres[3].x = -10.0f; spheres[3].z = 10.0f;
    spheres[4].x = 10.0f; spheres[4].z = -10.0f;
    for(unsigned int i = 0; i < 5; ++i)
        spheres[i].y = 0.5f;
    */
}

void render()
{
   while(1)
   {
        while(XPending(rscreen.getDisplay()))
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
                case KeyRelease:
                     release();
                     break;
                case MotionNotify:
                    handleMouse();
                    break;
            }
            draw();
            usleep(500);
        }
   }
}

void draw()
{
    rscreen.View();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.88f, 0.93f, 0.93f, 1.0f);
    //DRAW OTHER OBJECST BETWEEN SCREEN VIEW AND BUFFER
    levelone.draw();
    opposition.draw();
    for(unsigned int i = 0; i < 5; ++i)
        spheres[i].draw();

    float deltaX = mouse.getdelX();
    float deltaY = mouse.getdelY();
    player.render(deltaX, deltaY);
    glFinish();
    rscreen.Buffer();
}

void handleKeys()
{    
    mouse.reset(0);    
    keyboard.keyDown(rscreen.getEvent());
    if(keyboard.isKeyDown(XK_Up))
    {
        player.moveForward(0.0625);
    }
    if(keyboard.isKeyDown(XK_Left))
    {
        player.moveLeft(0.0625);
    }
    if(keyboard.isKeyDown(XK_Right))
    {
        player.moveRight(0.0625);
    }
    if(keyboard.isKeyDown(XK_Down))
    {
        player.moveBackward(0.0625);
    }
    if(keyboard.isKeyDown(XK_space))
    {
        player.fire();
    }
    if(keyboard.isKeyDown(XK_Escape))
    {
        rscreen.Close();
        exit(0);
    }
    release();
}

void release()
{
    keyboard.keyUp(rscreen.getEvent());
}

void handleMouse()
{
    mouse.onMove(rscreen.getEvent(), rscreen.getWidth(), rscreen.getHeight());    
}

void lighting()
{
    float light_position[] = {0.0, 20.0, 1.0, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light_position);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, YELLOW);
    glLightfv(GL_LIGHT0, GL_AMBIENT, BLACK);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
}
