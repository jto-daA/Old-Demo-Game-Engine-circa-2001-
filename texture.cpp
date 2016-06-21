/***********************************************
 * $author: javery
 * $date  : 26 Nov 01
 * $descp : texture management struct/routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\texture.h
 * $ver   : 0.0.0
 ***********************************************/

#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "texture.h"

static k_word textureCount=0;	

static void R_Tx_InitTexture(  GLenum mmFilter , GLenum mxFilter , k_word textureRef )
{
	glBindTexture( GL_TEXTURE_2D , textureRef );
	
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , mmFilter );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , mxFilter );
}

k_word R_Tx_LoadTexture( char* sFileName )
{
	AUX_RGBImageRec* texImage; 
	FILE* pTexFile = fopen( sFileName , "rb" );

	if( pTexFile == NULL )
	{
		MessageBox( NULL , "Unable to load specified texture file","R_Tx_LoadTexture fault", MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage( 0 );
		return 0xFFFF;
	}

	else
	{
		texImage = auxDIBImageLoad( sFileName );
	}

	R_Tx_InitTexture( GL_LINEAR , GL_LINEAR , textureCount );

	gluBuild2DMipmaps( GL_TEXTURE_2D,
		               3,
					   texImage->sizeX,
					   texImage->sizeY,
					   GL_RGB,
					   GL_UNSIGNED_BYTE,
					   texImage->data );
	
	textureCount++;
	return textureCount-1;
}

void R_Tx_UseTexture( k_word texIndex )
{
	glBindTexture( GL_TEXTURE_2D , texIndex );
}

//
// Builds a texture from the passed byte buffer
// 
k_word R_Tx_BuildTexture( k_word xDimen , k_word yDimen , k_byte depth , void* byteBuffer )
{
	R_Tx_InitTexture( GL_LINEAR , GL_LINEAR , textureCount );
	glTexImage2D( GL_TEXTURE_2D , 
		          0 ,
				  3 ,
				  xDimen,
				  yDimen,
				  0,
				  GL_COLOR_INDEX,
				  GL_BYTE,
				  byteBuffer );

	textureCount++;
	  
	return textureCount-1;
}