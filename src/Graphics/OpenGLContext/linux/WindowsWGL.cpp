
#define GL_GLEXT_PROTOTYPES 1
#include "WindowsWGL.h"
#include <Config.h>
#include <GLideN64.h>
#include <Graphics/OpenGLContext/GLFunctions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

static SDL_Window *_wind = NULL;
void WindowsWGL_GrabWindow(SDL_Window *wind) {
	_wind = wind;
}

bool WindowsWGL::start()
{
	initGLFunctions();
	return true;
}

void WindowsWGL::stop()
{
	/* Do Nothing. */
}

void WindowsWGL::swapBuffers()
{
	SDL_GL_SwapWindow(_wind);
}
