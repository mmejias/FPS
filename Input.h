#ifndef INPUT_H
#define INPUT_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>


class KeyboardHandler
{
    public:
        KeyboardHandler();
        ~KeyboardHandler();
        bool isKeyDown(unsigned int);
        bool isKeyUp(unsigned int);
        void keyDown(XEvent);
        void keyUp(XEvent);
    protected:
        bool* keyStates;
};

KeyboardHandler::KeyboardHandler()
{
    keyStates = new bool[65536];
}

KeyboardHandler::~KeyboardHandler()
{
    delete [] keyStates;
}

void KeyboardHandler::keyDown(XEvent keyEvent)
{
    //For a key down set the index in bool array to true
    
    switch(XLookupKeysym(&keyEvent.xkey, 0))
    {
        case XK_Escape: 
            keyStates[XK_Escape] = true;
            break;
        case XK_Left:
            keyStates[XK_Left] = true;
            break;
        case XK_Right:
            keyStates[XK_Right] = true;
            break;
        case XK_Up:
            keyStates[XK_Up] = true;
            break;
        case XK_Down:
            keyStates[XK_Down] = true;
            break;
        case XK_space:
            keyStates[XK_space] = true;
            break;
    }
   
}

void KeyboardHandler::keyUp(XEvent keyEvent)
{
    //For a key up set the index in bool array to false
    
    switch(XLookupKeysym(&keyEvent.xkey, 0))
    {
        case XK_Escape:
            keyStates[XK_Escape] = false;
            break;    
        case XK_Left:
            keyStates[XK_Left] = false;
            break;
        case XK_Right:
            keyStates[XK_Right] = false;
            break;
        case XK_Up:
            keyStates[XK_Up] = false;
            break;
        case XK_Down:
            keyStates[XK_Down] = false;
            break;
        case XK_space:
            keyStates[XK_space] = false;
            break;
    }
   
}

bool KeyboardHandler::isKeyDown(unsigned int key)
{
    return keyStates[key];
}

bool KeyboardHandler::isKeyUp(unsigned int key)
{
    return keyStates[key];
}

class MouseHandler
{
    public:
        MouseHandler();
        MouseHandler(int, int);
        float getX();
        float getY();
        float getdelX();
        float getdelY();
        void onMove(XEvent, int, int);
    protected:
        bool leftPress, rightPress;
        float xpos, ypos;
        float prevx, prevy;
        float deltaX, deltaY;
};

MouseHandler::MouseHandler()
{
    xpos = ypos = 0.0f; 
    prevx = prevy = 0.0f;
    leftPress = rightPress = false;
    deltaX = deltaY = 0.0f;
}   

MouseHandler::MouseHandler(int width, int height)
{
    xpos = float(width/2);
    ypos = float(height/2);
    deltaX = deltaY = 0.0f;
}

float MouseHandler::getdelX()
{
    return deltaX;
}

float MouseHandler::getdelY()
{
    return deltaY;
}

float MouseHandler::getX()
{
    return xpos;
}

float MouseHandler::getY()
{
    return ypos;
}

void MouseHandler::onMove(XEvent event, int width, int height)
{
    prevx = xpos;
    prevy = ypos;
    xpos = event.xmotion.x;
    ypos = event.xmotion.y;
    deltaX = xpos - prevx;
    deltaY = ypos - prevy;
}

#endif
