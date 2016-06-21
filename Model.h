/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Data structure for engine models ( scene objects )
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Model.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __ENT_MODEL_H__
#define __ENT_MODEL_H__

#include "vector.h"
#include "polygon.h"
#include "util_common_h.h"

#define ENT_M_MAX_CHILDREN  30

typedef enum
{
	MT_3DS_MAX_3,
    MT_3DS_MAX_4,
	MT_ID_MD2,
	MT_ID_MD3,
	MT_KAOS_MOD
}ModelType_t;

enum AnimInterType_t
{
	AIT_LINEAR,
	AIT_TRIG,
	AIT_CUBIC
};

typedef struct AnimDef_t
{
	float interSpeed;
	AnimInterType_t iType;
	k_word frameCount;
}*pAnimDef_t;

/* New structs for keyframing data added 31 NOV 02 */
typedef struct GlobalKeyframe_t
{ 
	// chunk ID (IG_3DS_KEYFRAME_GBL_HEADER)
	k_word keyfrmVer;
	k_byte sceneName[13];
	long animationLenght;

	// chunk ID (IG_3DS_KEYFRAME_GBL_ACT_SEG)
	long initFrame,termFrame;	

    // chunk ID (IG_3DS_KEYFRAME_GBL_CURR_FRAME)
	long initCurrFrame;	
}*p3DS_GlobalKeyframe_t;  

// bejezus , this is tedium redefined...
struct TrackHeader_t 
{
	k_word smoothingFlag;
	long unk01,unk02,trackKeyCount;
};

struct KeyHeader_t
{
	long frameIndex;
	k_word tensionBiasFlag;
	float splineTension, splineContinuity, splineBias,keyEaseToValue,keyEaseFromValue;
};

struct NodeHeader_t
{
	k_byte objName[11];
	k_word flagsOne,flagsTwo,parentID; // NOTE MAX_INT indicates no parent node. 
};

struct PositionTrack_t
{
	TrackHeader_t posTrackHeader;
	KeyHeader_t posKeyHeader;
	Vect3_t trackPositionVector;
};

struct RotationTrack_t
{
	TrackHeader_t rotTrackHeader;
	KeyHeader_t rotKeyHeader;
	Vect3_t trackRotationVector;
	float rotationAngle;
};

struct ScaleTrack_t
{
	TrackHeader_t sclTrackHeader;
	KeyHeader_t sclKeyHeader;
	Vect3_t trackScaleVector;
};

typedef struct KeyframeData_t
{
	// header
	GlobalKeyframe_t globalKeyframe;
    // and the guts...
	k_word u_NodeID;
	NodeHeader_t nodeHeader;
	Vect3_t modelPivot;
	k_byte objectInstanceName[11];
	Vect3_t bbxMin , bbxMax;          // min/max vertices of objects bounding box.
	PositionTrack_t* pPositionTracks;
	RotationTrack_t* pRotationTracks;
}*pKeyframeData_t;

typedef struct MD2_AminStruct_t
{
	float interpSpeed;
	k_word currFrame;
}*pMD2_AnimStruct_t;

typedef struct Model_t
{
	KeyframeData_t keyframeData;
	//MD2_AnimStruct_t md2Frames;

	pPoly_t *pModelFaces;
	k_word vectCount,polyCount,Version,textureRef,childCount,currentChild;
	Vect3_t* vectors,**pVectors,*md2TexCoords,**pmd2Frames;
	Poly_t* polygons;
	Model_t* pChildren,*Parent;
	char *objectName;     
	char skinNames[10][64];  // dimensions allocated to suite md2 restraints
	char frameNames[20][16];
	ModelType_t type;
	
	void (*Renderer)(Model_t*);

	// internal structs used for model independent animation
	struct md2Animation_t
	{
		int currFrame, nextFrame;
		float interpFac;             // current point in interperlation [0 , 1 ]
		float interpSpd;             // speed of interperlation
	};

	k_boolean singleTexture,hasChildren;
}*pModel_t;

void ENT_M_LambertRenderer( pModel_t );
void ENT_M_GouraudRenderer( pModel_t );
void ENT_M_WireFrameRenderer( pModel_t );
void ENT_M_PWTextureRenderer( pModel_t );
void ENT_M_SkTextureRenderer( pModel_t );
pModel_t ENT_M_AddChild( pModel_t );
void ENT_M_InitStandAlone( pModel_t );
void ENT_M_InitHierarchy( pModel_t );
void MTP_Strip( pModel_t , pPolySet_t);

#endif /* __ENT_MODEL_H__ */


