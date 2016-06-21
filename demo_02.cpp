// demo to test md2 loader/animator 020520:1644

#include "md2loader.h"
#include "model.h"
#include "camera.h"
#include "required.h"
#include "texture.h"

#include <math.h>
#include <gl/gl.h>
#include <gl/glaux.h>

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR string , int WinArg )
{
	int rot=0,pos=0,dir=0;
	WndStruct w; w.xDimension = 700,w.yDimension=500;w.hInstance = hInstance;
	MSG m;
	OpenGL_Struct ogl;
	k_boolean complete=k_false;	

	Model_t test_char,test_wep;
	md2Struct_t md2_1,md2_2;


	Camera_t c1,c2,c3,c4,*pc=&c1;
	
	MTV_Init( c1.Position , 0 , 0 , 2000 );
	MTV_Init( c1.Direction , 0 , 0 , 0  );

	MTV_Init( c2.Position ,  0 , 0 , 1500 );
	MTV_Init( c2.Direction , 180 , 0 , 0 );

	MD2_LoadObject( &md2_1 , "knight.md2" , &test_wep );
	//test_wep.textureRef = R_Tx_LoadTexture( "drfreak.tga" );
    //MD2_LoadObject( &md2_2 , "tris.md2" ,  &test_char  );

    ogl.contextDepth = 16;
	ogl.contextPitch = 640;
	ogl.fullScreen = k_false;
	ogl.yResolution =   480;
	
	SYS_OGL_CreateContext(&ogl,&w);
	

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
		
			ENT_C_LookAt( pc );

			glRotatef( rot++ , 0 , 1 , 0 );

			glPushMatrix();			
			
			glTranslatef( c1.Position.xComponent , c1.Position.yComponent , c1.Position.zComponent );
			auxWireSphere( 2.0f );
			
			glPushMatrix();

			glTranslatef( c2.Position.xComponent , c2.Position.yComponent , c2.Position.zComponent );
			auxWireSphere( 2.0f );

			glPopMatrix();
			glPopMatrix();
			
			(*test_wep.Renderer)( &test_wep );

			SwapBuffers( ogl.hDeviceContext );

			if( rand()%200 == 150 )
			{
				if(pc ==&c1 )
				{
					pc=&c2;
				}

				else
				{
					pc=&c1;				
				}
			}

		}
	}

	SYS_OGL_KillContext( &ogl , &w );

	return m.wParam;
}
