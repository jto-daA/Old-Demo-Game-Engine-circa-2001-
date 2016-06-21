/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Data structure/routines for camera
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Camera.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "camera.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void ENT_C_LookAt( pCamera_t pc )
{
    glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslatef( -pc->Position.xComponent , -pc->Position.yComponent , -pc->Position.zComponent );
	glRotatef( pc->Direction.xComponent ,  0 , -1  ,  0 ) ; // yaw
	glRotatef( pc->Direction.yComponent , -1 ,  0  ,  0 );  // pitch
	glRotatef( pc->Direction.zComponent ,  0 ,  0  , -1 );  // row
}

void ENT_C_Move( pCamera_t pc )
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslatef( pc->Position.xComponent , pc->Position.yComponent , pc->Position.zComponent );

}




