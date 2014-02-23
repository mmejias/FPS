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

RScreen rscreen;
Level levelone;
KeyboardHandler keyboard;
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
                keyboard.keyDown(rscreen.getEvent());
                if(keyboard.isKeyDown(XK_Escape))
                {
                    rscreen.Close();
                    exit(0);
                }
                draw();
                break;
        }
   }
}

void draw()
{
    rscreen.View();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //DRAW OTHER OBJECST BETWEEN SCREEN VIEW AND BUFFER
    levelone.draw();

    rscreen.Buffer();
}
