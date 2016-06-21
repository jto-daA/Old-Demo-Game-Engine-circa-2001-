/***********************************************
 * $author: javery
 * $date  : 13 Nov 01
 * $descp : OpenGL context/rudimentary routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\OpenGL.h
 * $ver   : 0.0.0
 ***********************************************/

#include "util_common.h"
#include "win32.h"

#ifndef __SYS_OPENGL_H__
#define __SYS_OPENGL_H__

#include <windows.h>
#include <gl/gl.h>

#define SYS_OGL_DEFAULT_FOV              45.0f
#define SYS_OGL_DEFAULT_FRUSTRUM_NEAR     0.1f
#define SYS_OGL_DEFAULT_FRUSTRUM_FAR   10000.0f

typedef struct
{
	k_word contextPitch,yResolution,contextDepth,contextPixelFormat;
	HGLRC glContext;
	HDC hDeviceContext;
	k_boolean fullScreen;
}OpenGL_Struct,*pOpenGL_Struct;

void SYS_OGL_CreateContext( pOpenGL_Struct , pWndStruct );
void SYS_OGL_KillContext( pOpenGL_Struct , pWndStruct );
void SYS_OGL_ResizeContext( k_word , k_word );
void SYS_OGL_SetStates( void );
void SYS_OGL_PrepFrame( void );

#endif 

