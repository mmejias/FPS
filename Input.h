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
    /*
    switch(XLookupKeySym(&keyEvent.xkey, 0))
    {
    
    }
    */
}

void KeyboardHandler::keyUp(XEvent keyEvent)
{
    //For a key up set the index in bool array to false
    /*
    switch(XLookupKeySym(&keyEvent.xkey, 0))
    {
        
    }
    */
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
    protected:
        bool leftPress, rightPress;
        int xpos, ypos;
};

MouseHandler::MouseHandler()
{
    xpos = ypos = 0; 
    leftPress = rightPress = false;
}   

