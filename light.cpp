/***********************************************
 * $author: javery
 * $date  : 19 Dec 01
 * $descp : lighting support.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\light.h
 * $ver   : 0.0.0
 ***********************************************/

#include <windows.h>
#include <gl/gl.h>

#include "light.h"
#include "vector.h"

void R_L_Init( GLenum glLight , pLightStruct pLight )
{
	static bInit=false;

	float tempPos[] = {  pLight->position.xComponent,
		                 pLight->position.yComponent,
						 pLight->position.zComponent  };

	glLightfv( glLight , GL_AMBIENT , pLight->ambient.Components );
	glLightfv( glLight , GL_DIFFUSE , pLight->diffuse.Components );
	glLightfv( glLight , GL_SPECULAR , pLight->specular.Components );
	glLightfv( glLight , GL_POSITION , tempPos );

	if( !bInit )
	{
		glEnable( GL_LIGHTING );
	}

	glEnable( glLight );
}
