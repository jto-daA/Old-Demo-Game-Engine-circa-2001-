/***********************************************
 * $author: javery
 * $date  : 22 May 02 
 * $descp : structs/routines to load pcx files.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\bsp_comp.h
 * $ver   : 0.0.0
 ***********************************************/

#include "pcx.h"
#include "texture.h"

#include <stdio.h>
#include <windows.h>
#include <memory.h>

static void BTMP_PCX_LoadHeader( FILE* pf , ppcxHeader_t ppcxh )
{
	rewind( pf );

	fread( &ppcxh->Manufacturer ,    sizeof(k_byte) , 1  , pf );
	fread( &ppcxh->Version      ,    sizeof(k_byte) , 1  , pf );
	fread( &ppcxh->Encoding     ,    sizeof(k_byte) , 1  , pf );
	fread( &ppcxh->BitsPerPixel ,    sizeof(k_byte) , 1  , pf );
	fread( &ppcxh->xWinMin      ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->yWinMin      ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->xWinMax      ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->yWinMax      ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->HorzResDPI   ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->VertResDPI   ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->Palette      ,    sizeof(k_byte) , 48 , pf );
	fread( &ppcxh->Reserved     ,    sizeof(k_byte) , 1  , pf );
	fread( &ppcxh->colorPlaneCount , sizeof(k_byte) , 1  , pf );
	fread( &ppcxh->BytesPerLine ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->PaletteInfo  ,    sizeof(k_word) , 1  , pf );
	fread( &ppcxh->HorScreenSize ,   sizeof(k_word) , 1  , pf );
	fread( &ppcxh->VerScreenSize ,   sizeof(k_word) , 1  , pf );
	fread( &ppcxh->Filler       ,    sizeof(k_byte) , 54 , pf );
}
//
// decodes a RLE pcx file
//
k_word BTMP_PCX_LoadBitmap( char* filename , ppcxStruct_t ppcx )
{
	FILE* fp = fopen( filename , "rb" );
	int sizeX=0,sizeY=0,size=0,depth=0,index=0;

	if( filename==NULL )
	{
		MessageBox( NULL , "Unable to find specified file in search path" , "BTMP_PCX_LoadHeader fault" , MB_ICONEXCLAMATION | MB_OK );
        PostQuitMessage(0);
		return -1;
	}

	BTMP_PCX_LoadHeader( fp , &ppcx->header );

	sizeX = 1+(ppcx->header.xWinMax - ppcx->header.xWinMin);
	sizeY = 1+(ppcx->header.yWinMax - ppcx->header.yWinMin);
	size=sizeX*sizeY;
	depth = ppcx->header.BitsPerPixel;

	// this code may have to change a bit if strange allocation error creep up...
	ppcx->buffer=new byte[size];
	memset( ppcx->buffer , 0 , sizeof(byte)*size );

	while( index<size ) 
	{
		byte read=fgetc(fp);

		if( (read >= 192) && (read<=255) )
        // RLE run.
		{
			int runLenght = read-192;
			read = fgetc(fp);

			while(runLenght--)
			{			
				ppcx->buffer[index++] = read;
			}
		}

		else
		{
			ppcx->buffer[index++] = read;
		}
	}

	fclose(fp);

	// Create ogl texture
	ppcx->glTexRef =  R_Tx_BuildTexture( sizeX , sizeY , depth , ppcx->buffer );
	return ppcx->glTexRef;
}