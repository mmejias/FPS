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
Level levelone;
KeyboardHandler keyboard;
MouseHandler mouse;
Player player;

int main(int argc, char** argv)
{
    initialize();
    render();

    return 0;
}

void initialize()
{
    rscreen.Initialize();
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
                printf("Key Pressed, Oh Lawdy!\n");
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

    player.render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //DRAW OTHER OBJECST BETWEEN SCREEN VIEW AND BUFFER
    levelone.draw();
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
    float prevx, prevy;

    prevx = mouse.getX();
    prevy = mouse.getY();
    mouse.onMove(rscreen.getEvent());
    player.rotateX(mouse.getX() - prevx);
}
