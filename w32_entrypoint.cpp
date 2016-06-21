/***********************************************
 * $author: javery
 * $date  : 27 Oct 01
 * $descp : prorgram entry point
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\w32_entrypoint.cpp
 * $ver   : 0.0.0
 ***********************************************/


#include "required.h"

#include "model.h"
#include "import_geo.h"
#include "import_3ds.h"

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLineArgs , int iWinArg )
{
	WndStruct w; w.xDimension = 300,w.yDimension=300;w.hInstance = hInstance;
	MSG m;
	OpenGL_Struct ogl;
	k_boolean complete=k_false;	

    ogl.contextDepth = 16;
	ogl.contextPitch = 640;
	ogl.fullScreen = k_false;
	ogl.yResolution =   480;
	
	SYS_OGL_CreateContext(&ogl,&w);	

	Model_t debugMe1;//,debugMe2;

	IG_3DS_LoadObject( &debugMe1 , "working.3ds" );

/*	while( complete==k_false )
	{
		if( PeekMessage( &m , w.hWnd , 0 , 0 , PM_REMOVE) )
		{
	        if( m.message == WM_QUIT || m.message == WM_CLOSE || m.message == WM_DESTROY )
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

		//	debugMe2.Renderer( &debugMe1 );

			SwapBuffers( ogl.hDeviceContext );
		}

		
	}*/

	SYS_OGL_KillContext( &ogl , &w );

	return m.wParam;
 
}

