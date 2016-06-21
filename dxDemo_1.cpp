
#include "DxWrapper.h"
#include "required.h"

extern HINSTANCE hInstance;
extern WndStruct wndStruct;

int WINAPI WinMain( HINSTANCE hthisInstance , HINSTANCE hPrevInstance , LPSTR lpCmdArgs , int iWinArg )
{
	hInstance=hthisInstance;

	wndStruct.xDimension = 300,wndStruct.yDimension=300;wndStruct.hInstance = hInstance;
	
	MSG m;
	OpenGL_Struct ogl;
	k_boolean complete=k_false;	

    ogl.contextDepth = 16;
	ogl.contextPitch = 640;
	ogl.fullScreen = k_false;
	ogl.yResolution =   480;
	
	SYS_OGL_CreateContext(&ogl,&wndStruct);	
	DX_InitInterfaces();
		
	while( complete==k_false )
	{
		if( PeekMessage( &m , wndStruct.hWnd , 0 , 0 , PM_REMOVE) )
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
			DX_GetDeviceStates();
			SYS_OGL_PrepFrame();
			
			SwapBuffers( ogl.hDeviceContext );
		}
	}

	SYS_OGL_KillContext( &ogl , &wndStruct );

	return m.wParam;


}