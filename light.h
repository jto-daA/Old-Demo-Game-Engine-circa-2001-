/***********************************************
 * $author: javery
 * $date  : 19 Dec 01
 * $descp : lighting support.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\light.h
 * $ver   : 0.0.0 basic openGL lighting functionality added
 *          0.0.1 light map stuff added. 
 ***********************************************/

#ifndef __R_LIGHT_H__
#define __R_LIGHT_H__

#include <windows.h>
#include <gl/gl.h>

#include "util_common_h.h"
#include "vector.h"

#define RED             0x0
#define GREEN           0x1
#define BLUE            0x2
#define ALPHA           0x3

typedef struct rgbaEnt
{
	float Components[4];
}*prgabEnt;

typedef struct LightStruct
{
	Vect3_t position,direction;
	rgbaEnt ambient,diffuse,specular;
}*pLightStruct;

void R_L_Init( GLenum , pLightStruct );

#endif /* __R_LIGHT_H__ */