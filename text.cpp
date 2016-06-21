/***********************************************
 * $author: javery
 * $date  : 06 jun 02
 * $descp : routines to support openGL scalable
 *          system fonts.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\text.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "text.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <stdarg.h>
#include <stdio.h>

static int glDispListInx=0;
static GLYPHMETRICSFLOAT gmFloats[ 256 ];

HFONT Txt_wglBuildFont( char* fontName , int scale , int paramA , int paramB , HDC hDC )
{
	HFONT hFont;

	// alloc space for the fonts display list.
	glDispListInx = glGenLists( 256 );

	// create font using gdi function.
	hFont = CreateFont( -scale , 
		                 0 , 
						 0 , 
						 0 , 
						 FW_BOLD , 
						 k_false , 
						 k_false , 
						 k_false , 
						 ANSI_CHARSET ,
						 OUT_TT_PRECIS , 
						 CLIP_DEFAULT_PRECIS , 
						 ANTIALIASED_QUALITY ,
						 FF_DONTCARE | DEFAULT_PITCH , 
						 fontName );

	if( hFont==NULL )
	{
		MessageBox( NULL , "Unable to create the specified font" , "Txt_wglCreateFont fault" , MB_OK | MB_ICONEXCLAMATION );
        PostQuitMessage(0);
	}

	SelectObject( hDC , hFont );

	wglUseFontOutlines( hDC , 
		                0 , 
						255 , 
						glDispListInx, 
						0.0f , 
						0.2f , 
						WGL_FONT_POLYGONS , 
						gmFloats );
	return hFont;
}

int Txt_wglPrint( char* string, float xPos , float yPos , float zPos )
{ 
	float length=0; 
    char text[256]; 
    va_list ap; 

    if (string == NULL) 
    return -1; 

    va_start(ap, string ); 
    vsprintf(text, string, ap); 
    va_end(ap); 

	for (unsigned int loop=0;loop<(strlen(text));loop++) // Loop To Find Text Length
	{
		length+=gmFloats[text[loop]].gmfCellIncX; // Increase Length By Each Characters Width
	}

	glPushMatrix();
	
	glTranslatef( xPos , yPos , zPos );

	glPushAttrib(GL_LIST_BIT); // Pushes The Display List Bits
    glListBase(glDispListInx); // 

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // Draws The Display List Text
    glPopAttrib(); 

	glPopMatrix();


    return loop;
}