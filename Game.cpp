#include "Level.h"
#include "Input.h"
#include "Player.h"
#include "RScreen.h"
#include "Enemy.h"

#include <cmath>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <unistd.h>
#include "Crosshair.h"

void alert();
void draw();
void initialize();
void render();
void update();
void release();
void handleEvents();
void handleKeys();
void handleMouse();
void lighting();

RScreen rscreen;
Level levelone("LevelOne.obj");
KeyboardHandler keyboard;
MouseHandler mouse(rscreen.getWidth(), rscreen.getHeight());
Player player;
Enemy opposition[5];
Crosshair reticle(rscreen.getWidth(), rscreen.getHeight());

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

    player.position.z = -100.0f;
    opposition[0].position.x = -10.0f;  opposition[0].position.z = -10.f;
    opposition[1].position.x = 10.0f;   opposition[1].position.z = 10.0f;
    opposition[2].position.x = 0.0f;    opposition[2].position.z = 0.0f;
    opposition[3].position.x = 10.0f;   opposition[3].position.z = -10.0f;
    opposition[4].position.x = -10.0f;  opposition[4].position.z = 10.0f;

    for(unsigned int i = 0; i < 5; ++i)
    {
        player.registerObserver(opposition[i]);
    }
}

void alert()
{
    for(unsigned int i = 0; i < 5; ++i)
    {
        if((std::fabs(opposition[i].position.x - player.position.x) <= 20.0  ||
            std::fabs(opposition[i].position.z - player.position.z) <= 20.0) &&
            !opposition[i].pathExists())
            {
                player.notifyObserver(opposition[i].getId()); 
                printf("Notifying observer %d\n", (int)opposition[i].getId());
            }
    }
}

void render()
{
   double timeDelta = 1000.0/24.0;
   double timeAccumulator = 0.0;
   
   while(1)
   {
        clock_t currentTime;
        clock_t startTime = clock();
        
        while(XPending(rscreen.getDisplay()))
        //while(timeAccumulator >= timeDelta )
        {
            timeAccumulator -= timeDelta;
            
            rscreen.Draw();
            
            handleEvents();
             
            currentTime = clock();
            timeAccumulator += double(currentTime - startTime);
        }

        draw();
   }
}

void draw()
{
    rscreen.View();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.88f, 0.93f, 0.93f, 1.0f);
    //DRAW OTHER OBJECST BETWEEN SCREEN VIEW AND BUFFER
    levelone.draw();

    for(unsigned int i = 0; i < 5; ++i)
    {
        opposition[i].update();
        opposition[i].draw();
    }

    float deltaX = mouse.getdelX();
    float deltaY = mouse.getdelY();

    reticle.draw();

    player.render(deltaX, deltaY);

    glFinish();
    rscreen.Buffer();
}

void handleEvents()
{

            switch(rscreen.getEvent().type)
            {
                case Expose:
                    draw();
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
                case LeaveNotify:
                    mouse.onMove(rscreen.getEvent(), rscreen.getWidth(), rscreen.getHeight());    
                    break;
            }
}

void handleKeys()
{    
    mouse.reset(0);    
    keyboard.keyDown(rscreen.getEvent());
    if(keyboard.isKeyDown(XK_Up))
    {
        player.moveForward(1.0f);
    }
    if(keyboard.isKeyDown(XK_Left))
    {
        player.moveLeft(1.0f);
    }
    if(keyboard.isKeyDown(XK_Right))
    {
        player.moveRight(1.0f);
    }
    if(keyboard.isKeyDown(XK_Down))
    {
        player.moveBackward(1.0f);
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
