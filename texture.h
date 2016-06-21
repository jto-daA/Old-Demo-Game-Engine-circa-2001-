/***********************************************
 * $author: javery
 * $date  : 26 Nov 01
 * $descp : texture management struct/routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\texture.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __R_TEXURE_H__
#define __R_TEXURE_H__

#include <windows.h>
#include <gl/gl.h>

#include "util_common_h.h"

k_word R_Tx_LoadTexture( char* );
k_word R_Tx_BuildTexture( k_word , k_word , k_byte , void* );
static void R_Tx_InitTexture( GLenum , GLenum , k_word );
void R_Tx_UseTexture( k_word );

#endif