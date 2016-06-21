/***********************************************
 * $author: javery
 * $date  : 8 Dec 01
 * $descp : BSP renderer.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\bsp_ren.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __R_BSP_MAIN__
#define __R_BSP_MAIN__

#include "bsp_comp.h"
#include "camera.h"

void R_BSP_RenderNode( pbspNode_t ,pCamera_t );
void R_BSP_RecurseRootNode( pbspNode_t , pCamera_t );		

#endif