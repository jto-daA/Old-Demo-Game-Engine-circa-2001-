/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Data structure/routines for camera
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Camera.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __ENT_CAMERA_H__
#define __ENT_CAMERA_H__

#include "util_common_h.h"
#include "vector.h"

typedef struct 
{
	Vect3_t Position,Direction;
	float angDiff;
}Camera_t,*pCamera_t;

void ENT_C_LookAt( pCamera_t );

#endif
