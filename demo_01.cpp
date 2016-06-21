///////////////////////////////////////////////////////////////
// Camera debugging application  (05/17/02:2156)
///////////////////////////////////////////////////////////////
#include "camera.h"
#include "util_common_h.h"
#include "win32.h"
#include "opengl.h"

#include <windows.h>
#include <gl/gl.h>
#include <math.h>

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR string , int WinArg )
{
	int i=0,pos=0,dir=0;
	Camera_t cam01;
	WndStruct w; w.xDimension = 500,w.yDimension=500;w.hInstance = hInstance;
	MSG m;
	OpenGL_Struct ogl;
	k_boolean complete=k_false;	

    ogl.contextDepth = 16;
	ogl.contextPitch = 640;
	ogl.fullScreen = k_false;
	ogl.yResolution =   480;
	
	SYS_OGL_CreateContext(&ogl,&w);

	cam01.angDiff = 1.0f;
	MTV_Init( cam01.Direction , 0 , 45 , 0 );
	MTV_Init( cam01.Position  , 0 , 0 , 10 );

	while( complete==k_false )
	{
		if( PeekMessage( &m , w.hWnd , 0 , 0 , PM_REMOVE) )
		{
	        if( m.message == WM_QUIT )
			{
				PostQuitMessage( 0 );
				complete = k_true;
			}
			
			else
			{
				TranslateMessage( &m );
				DispatchMessage( &m );
			}
		}

		else
		{
			SYS_OGL_PrepFrame();
			glLoadIdentity();

			ENT_C_LookAt( &cam01 );

			//cam01.Position.yComponent += sin(pos/10);
			
			pos++;
		
			glRotatef( i++ , 0 , -1 , 0 );
			

			glBegin( GL_QUADS );

			glColor3d( 0 , 1 , 0 );
			glVertex3d( -1 , 1 , 0 );
			
			glColor3d( 1 , 1 , 1 );
			glVertex3d( 1 , 1 , 0 );
			
			glColor3d( 0 , 0 , 1 );
			glVertex3d( 1 , -1 , 0 );

			glColor3d( 1 , 0 , 0 );
			glVertex3d( -1 , -1 , 0 );		
			
			glEnd();

			SwapBuffers( ogl.hDeviceContext );
		}
	}

	SYS_OGL_KillContext( &ogl , &w );

	return m.wParam;
}



