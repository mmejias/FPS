#ifndef RSCREEN_H
#define RSCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <unistd.h>

class RScreen
{
    public:
       RScreen();
       RScreen(int, int);
       Window getWindow();
       Display* getDisplay();
       int getWidth();
       int getHeight();
       XEvent getEvent();
       XEvent* getEventP();
       void View();
       void Initialize();
       void Draw();
       void Close();
       void Buffer();
    private:
       int width, height;
       Display*                 dpy;
       Window                   root;
       GLint*                   att;
       XVisualInfo*             vi;
       Colormap                 cmap;
       XSetWindowAttributes     swa;
       Window                   win;
       GLXContext               glc;
       XWindowAttributes        gwa;
       XEvent                   xev;
};

RScreen::RScreen ()
{
    width = 1000;
    height = 1000;
    att = new GLint[5];
    att[0] = GLX_RGBA;
    att[1] = GLX_DEPTH_SIZE;
    att[2] = 24;
    att[3] = GLX_DOUBLEBUFFER;
    att[4] = None;
    //{ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
}

RScreen::RScreen (int m_width, int m_height)
{
    width = m_width;
    height = m_height;
}

Window RScreen::getWindow()
{
    return root;
}

Display* RScreen::getDisplay()
{
    return dpy;
}

int RScreen::getWidth()
{
    return width;
}

int RScreen::getHeight()
{
    return height;
}

XEvent RScreen::getEvent()
{
    return xev;
}

XEvent* RScreen::getEventP()
{
    return &xev;
}

void RScreen::View()
{ 
    XGetWindowAttributes(dpy, win, &gwa);
    glViewport(0, 0, gwa.width, gwa.height);
}

void RScreen::Initialize()
{
    dpy = XOpenDisplay(NULL);
    if(dpy == NULL)
    {
        printf("\n\tcannot connect to X Server\n\n");
        printf("Bee Boop...Closing program\n");
        exit(0);
    }
    root = DefaultRootWindow(dpy);
    vi = glXChooseVisual(dpy, 0, att);
    
    if(vi == NULL)
    {
        printf("\n\tNo appropriate visual found\n\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid);
    }

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | PointerMotionMask;

    win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
                        CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Remington's Window");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

}

void RScreen::Draw()
{
    XNextEvent(dpy, &xev);
}

void RScreen::Close()
{
    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, glc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    exit(EXIT_SUCCESS);
}

void RScreen::Buffer()
{
    glXSwapBuffers(dpy, win);
    usleep(500);
}

#endif 
