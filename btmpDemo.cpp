///////////////////////////////////////////////////////////
// Demo to test bitmap/image format routines 210502:0839
///////////////////////////////////////////////////////////

#include "pcx.h"
#include "texture.h"

#include "required.h"

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR args , int winArg )
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
	
	pcxStruct_t img1;

	int i=0,ref=0;




	//BTMP_PCX_LoadBitmap("demo.pcx" , &img1 );
	ref=R_Tx_LoadTexture( "pic03.bmp" );
	

	
	
	
	glEnable( GL_TEXTURE_2D );
	
	
	
	
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

			glViewport( 0 , 0 , 150 , 150 );
 
			glTranslatef( 0 , 0 , -10 );
			glRotatef( i++ , 0 , 0 , 1 );
			R_Tx_UseTexture(ref);

			glBegin( GL_QUADS );
			   glTexCoord3d( 0 , 0 , 0 );
			   glVertex2d( -1, 1 );

			   glTexCoord3d( 1 , 0 , 0 );
			   glVertex2d( 1, 1 );

			   glTexCoord3d( 1 , 1 , 0 );
			   glVertex2d( 1, -1 );

			   glTexCoord3d( 0 , 1 , 0 );
			   glVertex2d( -1, -  1 );
             glEnd();

			 glTranslatef( 5 , 0 , -10 );
			 R_Tx_UseTexture( ref );

			 glViewport( 150 , 150 , 150 , 150 );
			 
			 glBegin( GL_QUADS );
			   glTexCoord3d( 0 , 0 , 0 );
			   glVertex2d( -1, 1 );

			   glTexCoord3d( 1 , 0 , 0 );
			   glVertex2d( 1, 1 );

			   glTexCoord3d( 1 , 1 , 0 );
			   glVertex2d( 1, -1 );

			   glTexCoord3d( 0 , 1 , 0 );
			   glVertex2d( -1, -  1 );
             glEnd();


		
			SwapBuffers( ogl.hDeviceContext );
		}
	}

	SYS_OGL_KillContext( &ogl , &w );

	return m.wParam;
}