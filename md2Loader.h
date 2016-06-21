/***********************************************
 * $author: javery
 * $date  : 20 May 02
 * $descp : Rotines to load and animate md2 models ( thanks to id software for
 *          this convienet file spec )
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\md2Loader.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __MD2_LOADER_H__
#define __MD2_LOADER_H__

#include "model.h"
#include "util_common_h.h"

#include <stdio.h>

#define MD2_MAX_TRI_COUNT          0x1000
#define MD2_MAX_VERT_COUNT         0x0800
#define MD2_MAX_TEX_COORD_COUNT    0x0800
#define MD2_MAX_FRAME_COUNT        0x0200
#define MD2_MAX_SKIN_COUNT         0x0200

typedef struct md2Struct_t
{
	int magic_id,
		version,
		skinWidth,
		skinHeight, 
		frameSize, 
		skinCount, 
		vertCount, 
		texCoordCount,
		triCount,
		glCmdCount,
		frameCount,
		skinOffset,
		texCoordOffset,
		triOffset,
		frameOffset,
		glCmdOffset,
	    endOffsetl;
}*pmd2Struct_t;

static void MD2_InitStruct( pmd2Struct_t , FILE* );
static __inline float MD2_TranslateVertex( float , float , k_byte  );
k_boolean MD2_LoadObject( pmd2Struct_t , char* , pModel_t );

#endif 
