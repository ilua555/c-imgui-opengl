module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>
#include <cstdio>
#pragma comment(lib, "opengl32.lib")
export module open_gl_draw;

using F_gldraw = void (__stdcall*)(GLenum mode, GLint first, GLsizei count);
export F_gldraw glDrawOriginal = nullptr;

export void __stdcall glDrawHook(GLenum mode, GLint first, GLsizei count) {
	printf("heello drawgl\n");
	glDisable(GL_DEPTH_TEST);
}