/***********************************************
 * $author: javery
 * $date  : 8 Dec 01
 * $descp : BSP compiler.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\bsp_comp.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __R_BSP_COMPILER__
#define __R_BSP_COMPILER__

#include "model.h"
#include "vector.h"	
#include "plane.h"

// Hmmm,, consider tweaking these weight factors later, */
#define NODE_DETMN_SPLIT_FAC   0.95f
#define NODE_DETMN_BALANCE_FAC 0.75f

enum NodeType
{
	NT_TREE,NT_LEAF
};

typedef struct bspNode_t
{
	pModel_t pObject;
	pPoly_t pPoly;
	bspNode_t* plChild,*prChild;
	Plane_t SplitPlane;
	k_boolean visited;
	NodeType type;
	k_boolean bVisited;
	PolySet_t Polys;
}*pbspNode_t;

typedef struct bspTree_t
{
	pbspNode_t treeBranches;
	k_word leafCount;
}*pbspTree_t;

static int R_BSP_SplitPolygon( pbspNode_t , int ,  pbspNode_t , int ,  pPlane_t , pPoly_t );
static int R_BSP_FindSplitPlane( pPolySet_t , int*, int*, int* , int*);
static pbspNode_t R_BSP_AddPolygon( pbspNode_t , pPoly_t );
void R_BSP_ConstructTree( pbspNode_t , pPolySet_t );
void R_BSP_ConstructTree( pbspNode_t );
void R_BSP_DeleteTree( pbspNode_t );

#endif