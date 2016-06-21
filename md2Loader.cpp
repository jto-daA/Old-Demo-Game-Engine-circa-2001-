/***********************************************
 * $author: javery
 * $date  : 20 May 02
 * $descp : Rotines to load and animate md2 models ( thanks to id software for
 *          this convienet file spec )
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\md2Loader.h
 * $ver   : 0.0.0
 ***********************************************/

#include "md2Loader.h"
#include "model.h"
#include "util_end_h.h"
#include "texture.h"

#include <stdio.h>

static void MD2_InitStruct( pmd2Struct_t pmd2 , FILE* fp )
{
	rewind( fp );
	
	pmd2->magic_id       = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->version        = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->skinWidth      = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->skinHeight     = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->frameSize      = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->skinCount      = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->vertCount      = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->texCoordCount  = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->triCount       = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->glCmdCount     = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->frameCount     = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->skinOffset     = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->texCoordOffset = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->triOffset      = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->frameOffset    = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->glCmdOffset    = UTL_SwitchEndian_ReadDWordFromFile( fp );
	pmd2->endOffsetl     = UTL_SwitchEndian_ReadDWordFromFile( fp );
}

static __inline float MD2_TranslateVertex( float scale , float trans , k_byte vComp )
{
	return (float)vComp + (scale*trans);
}

k_boolean MD2_LoadObject( pmd2Struct_t pmd2 , char *filename , pModel_t pMod )
{
	FILE* fp = fopen( filename , "rb" );
	int index=0;

	if( fp==NULL )
	{
		MessageBox( NULL , "specified file not found in search path" , "MD2_LoadObject fault" , MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return k_false;
	}
	
	// load in header info ////////////////////////////////////////////////////////////////
	MD2_InitStruct( pmd2 , fp );
	// alloc verticies/polygons/frames ////////////////////////////////////////////////////
	pMod->vectCount    = pmd2->vertCount;
	pMod->polyCount    = pmd2->triCount;
	pMod->vectors      = new Vect3_t[ pmd2->vertCount ];
	pMod->pVectors     = new pVect3_t[ pmd2->vertCount ];
	pMod->polygons     = new Poly_t[ pmd2->triCount ];
	pMod->pModelFaces  = new pPoly_t[ pmd2->triCount ];	
	pMod->md2TexCoords = new Vect3_t[ pmd2->texCoordCount ];
	pMod->pmd2Frames   = new pVect3_t[ pmd2->frameCount ];

	// load skin names ( if present ) /////////////////////////////////////////////////////
	if( pmd2->skinCount )
	{
		fseek( fp , pmd2->skinOffset , SEEK_SET );
		for(index=0;index < pmd2->skinCount;index++)
		{
			char tempSkinName[64];
			fread( tempSkinName , sizeof(char) , 64 ,  fp );
			memcpy( &pMod->skinNames[index] , tempSkinName , sizeof(char)*64);
		}
	}
	// load in texture coordinates ////////////////////////////////////////////////////////
	fseek( fp , pmd2->texCoordOffset , SEEK_SET );
	for(index=0;index<pmd2->texCoordCount;index++)
	{
		short u,v;
		fread( &u , sizeof(short) , 1 , fp );
		fread( &v , sizeof(short) , 1 , fp );	
		
		MTV_Init( pMod->md2TexCoords[index] , 0 , 0 , 0 );
		pMod->md2TexCoords[index].uComponent = u;
		pMod->md2TexCoords[index].vComponent = v;
	}

	// load in frames NOTE: frame 0 is default model definition set ////////////////////////
	fseek( fp , pmd2->frameOffset , SEEK_SET );
	for(index=0;index<pmd2->frameCount;index++)
	{
		float s1=0,s2=0,s3=0,t1=0,t2=0,t3=0;
		k_byte xComp=0,yComp=0,zComp=0;
		char* tempFrameName;

		pMod->pmd2Frames[index] = new Vect3_t[ pmd2->vertCount ];

		fread( &s1 , sizeof(float) , 1 , fp );
		fread( &s2 , sizeof(float) , 1 , fp );
		fread( &s3 , sizeof(float) , 1 , fp );
		
		fread( &t1 , sizeof(float) , 1 , fp );
		fread( &t2 , sizeof(float) , 1 , fp );
		fread( &t3 , sizeof(float) , 1 , fp );

		fread( &tempFrameName , sizeof(char) , 16 , fp );

		for(int index2=0;index2<pmd2->vertCount;index2++)
		{
			k_byte x=0,y=0,z=0,lightNormalIndex;

			fread( &x , sizeof(k_byte) , 1 , fp );
			fread( &y , sizeof(k_byte) , 1 , fp );
			fread( &z , sizeof(k_byte) , 1 , fp );
			fread( &lightNormalIndex , sizeof(k_byte) , 1 , fp );

			MTV_Init( pMod->pmd2Frames[index][index2] , 0 , 0 , 0 );
			pMod->pmd2Frames[index][index2].xComponent = MD2_TranslateVertex( s1 , t1 , x );
			// NOTE: the same weird z/y swap as in 3ds exsists here as well ( hmmmm )
			pMod->pmd2Frames[index][index2].zComponent = MD2_TranslateVertex( s2 , t2 , y );
			pMod->pmd2Frames[index][index2].yComponent = MD2_TranslateVertex( s3 , t3 , z );

			if( index==0 )
            // frame 0
			{
				pMod->vectors[index2] = pMod->pmd2Frames[index][index2];
				pMod->pVectors[index2] = &pMod->vectors[index2];	
			}
		}
	}

	// load in the polygon data /////////////////////////////////////////////////////////////
	fseek( fp , pmd2->triOffset , SEEK_SET );
	for(index=0;index<pmd2->triCount;index++)
	{
		short v1=0,v2=0,v3=0,t1=0,t2=0,t3=0;
		fread( &v1 , sizeof(short) , 1 , fp );
		fread( &v2 , sizeof(short) , 1 , fp );
		fread( &v3 , sizeof(short) , 1 , fp );
	
		fread( &t1 , sizeof(short) , 1 , fp );
		fread( &t2 , sizeof(short) , 1 , fp );
		fread( &t3 , sizeof(short) , 1 , fp );
		
		// Allocate space for vertex pointers.
		MTP_AllocTri( &pMod->polygons[index] );
		
		pMod->polygons[index].pVerticies[0] = pMod->pVectors[v1];
		pMod->polygons[index].pVerticies[1] = pMod->pVectors[v2];
		pMod->polygons[index].pVerticies[2] = pMod->pVectors[v3];

		pMod->polygons[index].pVerticies[0]->uComponent = pMod->md2TexCoords[t1].uComponent;
		pMod->polygons[index].pVerticies[0]->vComponent = pMod->md2TexCoords[t1].vComponent;

		pMod->polygons[index].pVerticies[1]->uComponent = pMod->md2TexCoords[t2].uComponent;
		pMod->polygons[index].pVerticies[1]->vComponent = pMod->md2TexCoords[t2].vComponent;

		pMod->polygons[index].pVerticies[2]->uComponent = pMod->md2TexCoords[t3].uComponent;
		pMod->polygons[index].pVerticies[2]->vComponent = pMod->md2TexCoords[t3].vComponent;

		pMod->pModelFaces[index] = &pMod->polygons[index];

		// Note; here I have decided to generate my own normals instead of those defined by id.
		MTP_MakeNormal( &pMod->polygons[index] );
		MTV_Normalize( pMod->pModelFaces[index]->Normal );		
	}
    
	// initialize remaining struct data /////////////////////////////////////////////////////
	pMod->childCount = 0;
	pMod->currentChild = NULL;
	pMod->hasChildren = k_false;
	pMod->objectName = pMod->skinNames[0];
	pMod->Parent = NULL;
	pMod->pChildren = NULL;
	//pMod->Renderer = ENT_M_SkTextureRenderer;
    pMod->Renderer = ENT_M_WireFrameRenderer; 
	pMod->singleTexture = k_true;
	//pMod->textureRef = R_Tx_LoadTexture( pMod->skinNames[0] );
	pMod->textureRef = 0;
	pMod->type = MT_ID_MD2;
	pMod->Version = pmd2->version;

	fclose( fp );
	return k_true;
} 