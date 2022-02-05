#pragma once
#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/wglext.h>
#include <windows/GLideN64_windows.h>

class WindowsWGL
{
public:
	static bool start();
	static void stop();
	static void swapBuffers();

private:
	static HGLRC hRC;
	static HDC hDC;
};

