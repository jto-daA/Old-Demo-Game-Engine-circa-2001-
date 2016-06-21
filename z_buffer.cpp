/***********************************************
 * $author: javery
 * $date  : 17 Dec 01
 * $descp : z-buffer based scene mgmt..
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\z_buffer.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "z_buffer.h"
#include <stdio.h>

void R_Z_RenderWorld( pCamera_t cam , pModel_t pmods )
// to heck with sophistication...
{
	ENT_C_LookAt( cam );

	for(int index=0;&pmods[index] != NULL;index++)
	pmods[index].Renderer( &pmods[index] );
}
