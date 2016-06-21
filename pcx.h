/***********************************************
 * $author: javery
 * $date  : 22 May 02 
 * $descp : structs/routines to load pcx files.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\bsp_comp.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __BTMP_PCX_H__
#define __BTMP_PCX_H__

#include "util_common_h.h"

#include <stdio.h>

typedef struct pcxHeader_t
// NOTE: pcx headers are set at a constant 128 byte size
{
	k_byte Manufacturer,
		   Version,
		   Encoding,          // 1-RLE encoded pixel data
		   BitsPerPixel,
		   Palette[48],
		   Reserved,
		   colorPlaneCount,
		   Filler[54];       // remaining bytes to complete 128 byte header. 
	k_word HorzResDPI,
		   VertResDPI,
		   xWinMin,yWinMin,
		   xWinMax,yWinMax,
		   BytesPerLine,
		   PaletteInfo,
		   HorScreenSize,
		   VerScreenSize;
}*ppcxHeader_t;

typedef struct pcxStruct_t
{
	pcxHeader_t header;
	k_byte* buffer;
	int glTexRef;
}*ppcxStruct_t;

static void BTMP_PCX_LoadHeader( FILE* , ppcxHeader_t );
k_word BTMP_PCX_LoadBitmap( char* , ppcxStruct_t );

#endif
