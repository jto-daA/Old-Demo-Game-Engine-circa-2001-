/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Routines to import data from AutoDesk 3D-
 *          Studio Max ( thanks to By Jeff Lewis (werewolf@worldgate.com) for the file spec )
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Import_geo.h
 * $ver   : 0.0.0
 ***********************************************/

#include "import_geo.h"
#include "vector.h"
#include "polygon.h"
#include "quaternion.h"
#include "util_end_h.h"
#include "mth_common.h"

#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <math.h>

static k_word chunkIDs[]=
{ 0xAFFF , 0x0100 , 0x3E3D , 0x7012 , 0x7011 , 0x7020 ,
  0x7001 , 0x1200 , 0x2100 , 0x4000 , 0x4010 , 0x4011 ,
  0x4012 , 0x4013 , 0x4014 , 0x4015 , 0x4016 , 0x4017 ,
  0x4100 , 0x4110 , 0x4111 , 0x4120 , 0x4130 , 0x4131 ,
  0x4140
};

static k_word IG_3DS_ReturnVersionNumber( FILE* p3DS_BinFile )
{
	long currentOffset = ftell( p3DS_BinFile );
	k_word version = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , IG_3DS_VERSION_OFFSET );
	fseek( p3DS_BinFile , currentOffset , SEEK_SET );

	return version;
}

static long IG_3DS_SkipChunk( k_word chunkID , FILE* p3DS_BinFile )
// there is a certain way that this is to be used...
{
	long chunkLenght=0,fileOffset = IG_3DS_FindChunkID( chunkID , p3DS_BinFile );
	chunkLenght = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) );
	
	if( fileOffset == 0xFFFFFFFF )
	{
		return ftell( p3DS_BinFile ); // I am sorry, but that one doesn't exsist
	}
	
	fseek( p3DS_BinFile , chunkLenght , SEEK_SET );
	
	return ftell( p3DS_BinFile );
}

static long IG_3DS_SkipToChunk( k_word chunkID , FILE* p3DS_BinFile )
{
	int index = 0;
	k_word what=0;
	long fileOffset=0;

	while( what != chunkID )
	{
		IG_3DS_SkipChunk( chunkIDs[ index ] , p3DS_BinFile );
		what = chunkIDs[ index++ ];
		fileOffset = ftell( p3DS_BinFile );
	}

    return ftell( p3DS_BinFile );
}

long IG_3DS_FindChunkID( k_word chunkID , FILE* p3DS_BinFile )
// a searching we will go.....
{
	long currentOffset = ftell( p3DS_BinFile );
	rewind( p3DS_BinFile );
	long fileLenght = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , 2 ); 
	fseek( p3DS_BinFile , currentOffset , SEEK_SET );

	for(long index = currentOffset;index < (fileLenght/*-currentOffset*/);index++)
	{
		if( UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile ,index ) == chunkID )
		{
    		return ftell( p3DS_BinFile);
		}
	}	

	for(index = currentOffset+1;index < (fileLenght/*-currentOffset*/);index++)
	{
		if( UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , index ) == chunkID )
		{
			return ftell( p3DS_BinFile );
		}
	}

	return 0xFFFFFFFF;
}

static void IG_3DS_LoadTexture( Model_t* pMod , FILE* p3DS_BinFile )
{
	// maintain file pointer here if necessary...But for now, I dont care.
	long currentOffset = ftell(p3DS_BinFile);
	k_word vertexCount = 0;
	rewind( p3DS_BinFile );
    //k_word fileLenght = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , 2 );
	//fseek(p3DS_BinFile,currentOffset,SEEK_SET);

	k_word fileRead=0;
	long textureChunkOffset=0;

//	for(long index=currentOffset;index<(fileLenght-currentOffset);index++)
    for(long index=0;/*index<fileLenght*/;index++) 
	{
		fileRead = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , index );
		
		if( fileRead == IG_3DS_ID_MAPPING_COORDS )
		{
			// Now check to see if this is the right chunk or not....
			fseek( p3DS_BinFile , 4 , SEEK_CUR );
			vertexCount = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

			if( vertexCount == pMod->vectCount )
			{
				textureChunkOffset = ftell( p3DS_BinFile );
				break;
			}
		}
	} 

    fseek( p3DS_BinFile , textureChunkOffset , SEEK_SET );

	for(int tIndex = 0;tIndex < pMod->vectCount;tIndex++)
	{
		fread(&pMod->vectors[ tIndex ].uComponent , sizeof(float),1,p3DS_BinFile);
		fread(&pMod->vectors[ tIndex ].vComponent , sizeof(float),1,p3DS_BinFile);
	}
}

static void IG_3DS_LoadChildren( Model_t* pMod , FILE* p3DS_BinFile )
{
	rewind( p3DS_BinFile );
    k_word fileLenght = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , 2 );
	rewind( p3DS_BinFile );

	char tempName[32];
	long objOffsets[ENT_M_MAX_CHILDREN]; // I hate code like this...
	Model_t* pCurrentChild=NULL;
	
	for(long index=0,index2=0;index < fileLenght;index++)
	{
		k_word fileRead = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , index );			   
	
		if( fileRead == IG_3DS_ID_OBJECT )
		{
			fseek( p3DS_BinFile , 4 , SEEK_CUR );
			
			do
			{
				index++; // keep the file pointer updated
				tempName[index2++] = fgetc(p3DS_BinFile);			   
			}while( (tempName[index2-1] != 0) && (index2 < 32));

		    fileRead = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

			if( fileRead == IG_3DS_ID_OBJECT_MESH )
			{
     			fseek( p3DS_BinFile , 4  , SEEK_CUR );

				fileRead = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile ) );

			    if( fileRead == IG_3DS_ID_VERTEX_ARRAY )
               	{
					pModel_t pChild = ENT_M_AddChild( pMod );
			        
					memcpy( pChild->objectName , tempName  , sizeof(char)*32 );
				
					objOffsets[ pMod->childCount++ ] = ftell( p3DS_BinFile );
				}
			}				

			index2=0; 
		}
	}

	pCurrentChild = pMod->pChildren;

	for(int __index=0;__index<pMod->childCount;__index++)
	{
    	fseek( p3DS_BinFile , objOffsets[ __index ] , SEEK_SET );
		pCurrentChild->hasChildren = k_false;
		pCurrentChild->childCount = 0;
		IG_3DS_LoadObject( pCurrentChild , p3DS_BinFile );
		pCurrentChild = pCurrentChild->pChildren;
	}
}

static void IG_3DS_LoadObject( Model_t* pObject , FILE* p3DS_BinFile )
// Dear god this is an awful hack....
{
	k_word vCount = 0,
		   pCount = 0,
		   version = pObject->Version = IG_3DS_ReturnVersionNumber( p3DS_BinFile );
	int dummy = 0;  // dummy is to hold an superflous file read
	
	long vectorOffset = IG_3DS_FindChunkID( IG_3DS_ID_VERTEX_ARRAY   , p3DS_BinFile ),
    	   polyOffset = IG_3DS_FindChunkID( IG_3DS_ID_FACE_INDICIES  , p3DS_BinFile ),
		   currentOffset = ftell( p3DS_BinFile );


	// first load in the vectors...
	fseek( p3DS_BinFile , vectorOffset , SEEK_SET );
	fread(&dummy,sizeof(int),1,p3DS_BinFile );
	pObject->vectCount = vCount = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) ),
    
    pObject->vectors = new Vect3_t[ vCount ];
	pObject->pVectors = new Vect3_t*[vCount];
	
	for( int index = 0;index < vCount;index++)
	{
		fread( &pObject->vectors[ index ].xComponent , sizeof(float) , 1 , p3DS_BinFile );
		/* Note that the strange 3ds y/z swap is accounted for */
		fread( &pObject->vectors[ index ].zComponent , sizeof(float) , 1 , p3DS_BinFile );
		fread( &pObject->vectors[ index ].yComponent , sizeof(float) , 1 , p3DS_BinFile );
		pObject->vectors[ index ].wComponent = 1;

		pObject->pVectors[ index ] = &pObject->vectors[ index ];
	}

	rewind( p3DS_BinFile );

	// Now load in the polygons...
	fseek( p3DS_BinFile , polyOffset , SEEK_SET );
	fread(&dummy,sizeof(int),1,p3DS_BinFile );
	pCount = pObject->polyCount = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) );

	pObject->polygons = new Poly_t[ pCount ];
	pObject->pModelFaces = new pPoly_t[ pCount ];

	for( index = 0;index < pCount;index++)
	{
		int index01   = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) ),
			index02   = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) ),
			index03   = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) ),
			// consider adding an element in Poly_t to support this flag
			index3DS  = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) );
		
		// This may cause a problem if I decide to decompose plain meshes into quad strips....
		MTP_AllocTri( &pObject->polygons[index] );

		pObject->polygons[ index ].pVerticies[ 0 ] = pObject->pVectors[ index01 ]; 
		pObject->polygons[ index ].pVerticies[ 1 ] = pObject->pVectors[ index02 ];
		pObject->polygons[ index ].pVerticies[ 2 ] = pObject->pVectors[ index03 ];

		pObject->polygons[index].Normal = MTP_MakeNormal( &pObject->polygons[ index ] );
		MTV_Normalize( pObject->polygons[index].Normal );
		pObject->pModelFaces[ index ] = &pObject->polygons[ index ];
	}

	
	// Now load in the texture space coordinates
	// IG_3DS_LoadTexture( pObject , p3DS_BinFile ); // THIS NEEDS TO BECOME CONDITIONAL TO PREVENT CRASHING...

	if( pObject->hasChildren && (pObject == pObject->Parent) )
	{
	//	IG_3DS_LoadChildren( pObject , p3DS_BinFile );
		IG_3DS_LoadObject( pObject , p3DS_BinFile );
	}

	// More to come ( next comes materials methinks.... )
	// added on 31 nov 02 
	// load in keyframe stuff. 
	IG_3DS_LoadGlobalKeyframeData( p3DS_BinFile , &pObject->keyframeData.globalKeyframe );
	IG_3DS_InitKeyframes( &pObject->keyframeData );
	IG_3DS_LoadKeyframeData( p3DS_BinFile , &pObject->keyframeData );
}

void IG_3DS_LoadObject( Model_t* pObject , char* sFileName )
{
	FILE* p3DS_BinFile = fopen( sFileName , "rb");
	
	if( p3DS_BinFile == NULL )
	{
		MessageBox( NULL , "Unable to find the specified object file","IG_3DS_LoadObject fault" , MB_OK );
		PostQuitMessage( 0 );
		return;
	}

	else
	{
		IG_3DS_LoadObject( pObject , p3DS_BinFile );
		fclose( p3DS_BinFile );
	}
}

static void IG_3DS_LoadGlobalKeyframeData( FILE* p3DS_BinFile , p3DS_GlobalKeyframe_t pgKeyframe )
{
	rewind( p3DS_BinFile );
	
	// find those offsets...
	long gblOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_GBL_HEADER     , p3DS_BinFile ),
		 actOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_GBL_ACT_SEG    , p3DS_BinFile ), 
		 frmOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_GBL_CURR_FRAME , p3DS_BinFile );
	
	// load global stuff
	fseek( p3DS_BinFile , gblOffset , SEEK_SET );
	pgKeyframe->keyfrmVer = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	fread( pgKeyframe->sceneName , sizeof(k_byte) , 13 , p3DS_BinFile );
	pgKeyframe->animationLenght = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

	// load active segment stuff
	fseek( p3DS_BinFile , actOffset, SEEK_SET );
    
	// do any empty read from this undocumented data value found... <-- TRY AND FIND OUT WHAT THIS REALY MEANS..
	UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile );

	pgKeyframe->initFrame = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	pgKeyframe->termFrame = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

	// load the initial frame
	fseek( p3DS_BinFile , frmOffset , SEEK_SET );
	UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile ); // <-- SAME THING GOES FOR THIS HERE.
	pgKeyframe->initCurrFrame = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
}

static void IG_3DS_InitKeyframes( pKeyframeData_t pKeyframe )
{
	// allocate space for the key frames.
	pKeyframe->pPositionTracks = new PositionTrack_t[ pKeyframe->globalKeyframe.animationLenght ];
	pKeyframe->pRotationTracks = new RotationTrack_t[  pKeyframe->globalKeyframe.animationLenght ];	
}

static void IG_3DS_LoadKeyframeData( FILE* p3DS_BinFile , pKeyframeData_t keyframeData )
// yes.... this qualifies as a hideous hack....
{
	// same-old same-o... get those offsets..
	long     objOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_NODE_OBJ , p3DS_BinFile ),
		  nodeIDOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_NODE_OBJ_NODE_ID , p3DS_BinFile ),
		 nodeHdrOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_NODE_OBJ_NODE_HDR , p3DS_BinFile ), 
		   pivotOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_NODE_OBJ_PIVOT , p3DS_BinFile ), // this may prove to be of some value
		  posTrxOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_NODE_OBJ_POS_TRACK , p3DS_BinFile ),
		  rotTrxOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_NODE_OBJ_ROT_TRACK , p3DS_BinFile ), 
		  sclTrxOffset = IG_3DS_FindChunkID( IG_3DS_KEYFRAME_NODE_OBJ_SCL_TRACK , p3DS_BinFile ),
		  unkwnObjectRef,unkwnNodeRef,unkwnPivotRef,unkwnPosKeyRef1,unkwnPosKeyRef2,unkwnRotKeyRef1,unkwnRotKeyRef2;
	float theta=0.0f;
	float currentAngle = 0.0f;

	Quaternion_t oldQ , workingQ,prodQ;        // quaternions used my Discreet to represent rotation. 
    MTQ_Init( &oldQ , 1.f , 0.f , 0.f , 0.f ); // set to identity to retain intial axial orientation.
	MTQ_Init( &workingQ , 0.f , 0.f , 0.f , 0.f );
	MTQ_Init( &prodQ , 0.f , 0.f , 0.f , 0.f );

	k_word tempFlag=0x0000;
	
	rewind( p3DS_BinFile );

	// load in this undocumented value
	fseek( p3DS_BinFile , objOffset , SEEK_SET );
	unkwnObjectRef = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

	// get the node ID
	fseek( p3DS_BinFile , nodeIDOffset, SEEK_SET );
	keyframeData->u_NodeID = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

	// load in the node header
	fseek( p3DS_BinFile , nodeHdrOffset , SEEK_SET );
	unkwnNodeRef = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );  // what is this?
	fread( keyframeData->nodeHeader.objName , sizeof(k_byte) , 11 , p3DS_BinFile );
	keyframeData->nodeHeader.flagsOne = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	keyframeData->nodeHeader.flagsTwo = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	keyframeData->nodeHeader.parentID = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

	// load in pivot point... 
	fseek( p3DS_BinFile , pivotOffset , SEEK_SET );
	unkwnPivotRef = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	fread( &keyframeData->modelPivot.xComponent , sizeof(float) , 1 , p3DS_BinFile ); 
	fread( &keyframeData->modelPivot.yComponent , sizeof(float) , 1 , p3DS_BinFile );
	fread( &keyframeData->modelPivot.zComponent , sizeof(float) , 1 , p3DS_BinFile );
	
	// load in position tracks ( weeeee!!! )
	fseek( p3DS_BinFile , posTrxOffset , SEEK_SET );

	// load track header ( note: TrackHeader stored in first array element...)
	keyframeData->pPositionTracks[0].posTrackHeader.smoothingFlag = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	keyframeData->pPositionTracks[0].posTrackHeader.unk01 =         UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	keyframeData->pPositionTracks[0].posTrackHeader.unk02 =         UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	keyframeData->pPositionTracks[0].posTrackHeader.trackKeyCount = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	// undocumented value.
	unkwnPosKeyRef1 =                                               UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );

// LOAD IN POSITIONAL TRACKS //////////////////////////////////////////////////////////////////////////////////////////	
	for(int index=0;index<keyframeData->globalKeyframe.animationLenght;index++)
	{
		// load key header
		keyframeData->pPositionTracks[ index ].posKeyHeader.frameIndex = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
		tempFlag = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
		
		if( tempFlag & 0x0001 )
		{
			fread( &keyframeData->pPositionTracks[ index ].posKeyHeader.splineTension , sizeof(float) , 1 , p3DS_BinFile );
		}
		
		if( tempFlag & 0x0002 )
		{
			fread( &keyframeData->pPositionTracks[ index ].posKeyHeader.splineContinuity , sizeof(float) , 1 , p3DS_BinFile );
		}

		if( tempFlag & 0x0004 )
		{
			fread( &keyframeData->pPositionTracks[ index ].posKeyHeader.splineBias , sizeof(float) , 1 , p3DS_BinFile );
		}

		if( tempFlag & 0x0008 )
		{
			fread( &keyframeData->pPositionTracks[ index ].posKeyHeader.keyEaseToValue , sizeof(float) , 1 , p3DS_BinFile );
		}

		if( tempFlag & 0x0010 )
		{
			fread( &keyframeData->pPositionTracks[ index ].posKeyHeader.keyEaseFromValue , sizeof(float) , 1 , p3DS_BinFile);
		}
		
		// now load the position key vertex
		fread( &keyframeData->pPositionTracks[ index ].trackPositionVector.xComponent , sizeof(float) , 1 , p3DS_BinFile );
		// same axis abnomality accounted for here...
		fread( &keyframeData->pPositionTracks[ index ].trackPositionVector.zComponent , sizeof(float) , 1 , p3DS_BinFile );
		fread( &keyframeData->pPositionTracks[ index ].trackPositionVector.yComponent , sizeof(float) , 1 , p3DS_BinFile );
	}

	// Load the Rotation Tracks key header
	fseek( p3DS_BinFile , rotTrxOffset , SEEK_SET );
	keyframeData->pRotationTracks[ 0 ].rotTrackHeader.smoothingFlag = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
	keyframeData->pRotationTracks[ 0 ].rotTrackHeader.unk01 =         UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) );
	keyframeData->pRotationTracks[ 0 ].rotTrackHeader.unk02 =         UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) );
	keyframeData->pRotationTracks[ 0 ].rotTrackHeader.trackKeyCount = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) );
	// undocumented values.
	unkwnRotKeyRef1 = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell( p3DS_BinFile ) );
	
// NOW, THE HARD PART: LOADING ROTATIONAL TRACKS, AND QUATERNIONS TO ROTATION MATRICIES //////////////////////////////////////
	for( int index2 = 0; index2 < keyframeData->pRotationTracks[0].rotTrackHeader.trackKeyCount;index2++)
	//  be aware that the conditon "keyframeData->pRotationTracks[0].rotTrackHeader.trackKeyCount" may have to be evaluated...
	{
		keyframeData->pRotationTracks[ index2 ].rotKeyHeader.frameIndex = UTL_SwitchEndian_ReadDWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
		tempFlag = UTL_SwitchEndian_ReadWordFromFile( p3DS_BinFile , ftell(p3DS_BinFile) );
		
		if( tempFlag & 0x0001 )
		{
			fread( &keyframeData->pRotationTracks[ index2 ].rotKeyHeader.splineTension , sizeof(float) , 1 , p3DS_BinFile );
		}
		
		if( tempFlag & 0x0002 )
		{
			fread( &keyframeData->pRotationTracks[ index2 ].rotKeyHeader.splineContinuity , sizeof(float) , 1 , p3DS_BinFile );
		}

		if( tempFlag & 0x0004 )
		{
			fread( &keyframeData->pRotationTracks[ index2 ].rotKeyHeader.splineBias , sizeof(float) , 1 , p3DS_BinFile );
		}

		if( tempFlag & 0x0008 )
		{
			fread( &keyframeData->pRotationTracks[ index2 ].rotKeyHeader.keyEaseToValue , sizeof(float) , 1 , p3DS_BinFile );
		}

		if( tempFlag & 0x0010 )
		{
			fread( &keyframeData->pRotationTracks[ index2 ].rotKeyHeader.keyEaseFromValue , sizeof(float) , 1 , p3DS_BinFile);
		}

		// read in the realative transforms
		fread( &keyframeData->pRotationTracks[ index2 ].rotationAngle   , sizeof(float) , 1 , p3DS_BinFile );
		
		// NOTE : because the stored angles are culmulative, swap the following values.
		keyframeData->pRotationTracks[ index2 ].rotationAngle *= 180/PI; // convert rad->deg
		currentAngle += keyframeData->pRotationTracks[ index2 ].rotationAngle;
		keyframeData->pRotationTracks[ index2 ].rotationAngle = currentAngle;

		// read the remaining axial data.
		fread( &keyframeData->pRotationTracks[ index2 ].trackRotationVector.xComponent , sizeof(float) , 1 , p3DS_BinFile ); 
		fread( &keyframeData->pRotationTracks[ index2 ].trackRotationVector.yComponent , sizeof(float) , 1 , p3DS_BinFile );
		fread( &keyframeData->pRotationTracks[ index2 ].trackRotationVector.zComponent , sizeof(float) , 1 , p3DS_BinFile );
	}
}
