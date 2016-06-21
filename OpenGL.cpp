/***********************************************
 * $author: javery
 * $date  : 13 Nov 01
 * $descp : OpenGL context/rudimentary routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\OpenGL.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "opengl.h"
#include "win32.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <memory.h>

/*
**************************************************
* SYS_OGL_KillContext 
* detaches and destroys openGL rendering context 
**************************************************
*/
void SYS_OGL_KillContext( pOpenGL_Struct pOGL , pWndStruct pWS )
{
	if( pOGL->fullScreen )
	{
		ChangeDisplaySettings( NULL , 0 );
		ShowCursor( k_true );
	}

	if( pOGL->glContext )
	{
		wglDeleteContext( pOGL->glContext );
		pOGL->glContext = NULL;
	}

	if( pOGL->hDeviceContext )
	{
		ReleaseDC( pWS->hWnd , pOGL->hDeviceContext );
		pOGL->hDeviceContext = NULL;
	}
} 
/*
**************************************************
* SYS_OGL_CreateContext 
* This funtion creates an OpenGL 32 rendering context
* of the specifed qualites within the already created 
* window.
**************************************************
*/
void SYS_OGL_CreateContext( pOpenGL_Struct pOGL , pWndStruct pWS )
{
	RECT contextRect;
	contextRect.bottom = pWS->yDimension;
	contextRect.left = 0;
	contextRect.right = pWS->xDimension;
	contextRect.top = 0;

	SYS_W32_RegisterClass( pWS );

	if( pOGL->fullScreen )
 	{
		DEVMODE dmScreenSettings;

		memset(&dmScreenSettings , 0 , sizeof(dmScreenSettings));

		dmScreenSettings.dmSize=sizeof(dmScreenSettings);	
		dmScreenSettings.dmPelsWidth	= pOGL->contextPitch;			
		dmScreenSettings.dmPelsHeight	= pOGL->yResolution;			
		dmScreenSettings.dmBitsPerPel	= pOGL->contextDepth;				
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","SYS_OGL_CreateContext fault",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				pOGL->fullScreen = k_false;								
			}
			else												
			{
				MessageBox(NULL,"Gee whiz... Perhaps you should invest\n in a new computer....","Your computer sucks!!!",MB_OK|MB_ICONSTOP);
				PostQuitMessage(0);
			}
		}

	}

	if( pOGL->fullScreen )
	{
		pWS->wExStyle = WS_EX_APPWINDOW;
		pWS->wStyle   = WS_POPUP;
	}

	else
	{
		pWS->wExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        pWS->wStyle   = WS_OVERLAPPEDWINDOW;
	}

	SYS_W32_CreateWindow( pWS );

	AdjustWindowRectEx( &contextRect ,
		                WS_OVERLAPPEDWINDOW ,
						k_false ,
						WS_EX_APPWINDOW | WS_EX_WINDOWEDGE );

	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),							// Size Of This Pixel Format Descriptor
		1,														// Version Number
		PFD_DRAW_TO_WINDOW |									// Format Must Support Window
		PFD_SUPPORT_OPENGL |									// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,										// Must Support Double Buffering
		PFD_TYPE_RGBA,											// Request An RGBA Format
		(unsigned char)pOGL->contextDepth,	        			// Select Our Color Depth
		0, 0, 0, 0, 0, 0,										// Color Bits Ignored
		0,														// No Alpha Buffer
		0,														// Shift Bit Ignored
		0,														// No Accumulation Buffer
		0, 0, 0, 0,												// Accumulation Bits Ignored
		0,														// No Z-Buffer (Depth Buffer)  
		0,														// No Stencil Buffer
		0,														// No Auxiliary Buffer
		PFD_MAIN_PLANE,											// Main Drawing Layer
		0,														// Reserved
		0, 0, 0													// Layer Masks Ignored
	};

	if(!(pOGL->hDeviceContext = GetDC( pWS->hWnd )) )
	{
		SYS_OGL_KillContext( pOGL , pWS );
		MessageBox( NULL , "Unable to create Win32 device context." , "SYS_OGL_CreateContext fault" , MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return;
	}

	if(!(pOGL->contextPixelFormat = ChoosePixelFormat( pOGL->hDeviceContext , &pfd )) )
	{
		SYS_OGL_KillContext( pOGL , pWS );
		MessageBox( NULL , "Unable to choose required pixel format","SYS_OGL_CreateContext fault.",MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return;
	}

	if(!SetPixelFormat( pOGL->hDeviceContext , pOGL->contextPixelFormat , &pfd ) )
	{
		SYS_OGL_KillContext( pOGL , pWS );
		MessageBox( NULL , "Unable to set required pixel format","SYS_OGL_CreateContext fault.",MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return;
	}

	if(!(pOGL->glContext = wglCreateContext( pOGL->hDeviceContext )) )
	{
		SYS_OGL_KillContext( pOGL , pWS );
		MessageBox( NULL , "Unable to create OpenGL rendering context.","SYS_OGL_CreateContext fault." , MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return;
	}

	if(!(wglMakeCurrent( pOGL->hDeviceContext , pOGL->glContext )) )
	{
		SYS_OGL_KillContext( pOGL , pWS );
		MessageBox( NULL , "error invoked by wglMakeCurrent","SYS_OGL_Error", MB_ICONEXCLAMATION | MB_OK );
		PostQuitMessage(0);
		return;
	}

	SYS_OGL_SetStates();
	SYS_OGL_ResizeContext( pWS->xDimension , pWS->yDimension );
}

/*
*********************************************
* SYS_OGL_ResizeContext
* recalculates the aspect ratio of the current
* context.
*********************************************
*/
void SYS_OGL_ResizeContext( k_word xNew , k_word yNew )
{
	if( !yNew )
	yNew = 1;

    glViewport(0, 0, xNew , yNew );
  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( SYS_OGL_DEFAULT_FOV, 
	               (float)(xNew/yNew) ,
				   SYS_OGL_DEFAULT_FRUSTRUM_NEAR ,
				   SYS_OGL_DEFAULT_FRUSTRUM_FAR );
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
*********************************************
* SYS_OGL_Init
* initializes the bare minimum openGL
* instrinsic states required for rendering.
*********************************************
*/
void SYS_OGL_SetStates( void )
{
	glShadeModel( GL_SMOOTH );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );

	glCullFace( GL_BACK );
}

/*
**********************************************
* SYS_OGL_Render
* Makes things happen....
**********************************************
*/
void SYS_OGL_PrepFrame( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
}
