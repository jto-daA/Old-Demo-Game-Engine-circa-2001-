/***********************************************
 * $author: javery
 * $date  : 8 Dec 01
 * $descp : BSP compiler.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\bsp_comp.h
 * $ver   : 0.0.0
 ***********************************************/

#include "plane.h"
#include "polygon.h"
#include "vector.h"
#include "bsp_comp.h"

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

/*
**************************************************
* R_BSP_SplitPolygon
* Splits the passed polygon into 2 seperate polygons 
* according to how the passed plane bisects it using
* a modified version of Sutherman-hodgeman clipping. 
**************************************************
*/
static int R_BSP_SplitPolygon( pbspNode_t pLeftChild , int lIndex , pbspNode_t pRightChild , int rIndex ,  pPlane_t pPartition , pPoly_t pSourcePoly )
// Hmmm... this code has managed to get a bit sloppy now has it not?
{
/*	pVect3_t rVectList[4],fVectList[4];
	float fOrient_1=0,fOrient_2=0;
	int fCount=0,rCount=0,iNumPolys=0,fxIndicies[2],rxIndicies[4];
	Vect3_t vIntersects[2];
	Vect3_t *pVect_1 = NULL,*pVect_2 = NULL;

	// section 1 : determine the intersections.
    for( int index=0;index<3;index++)
	{
		pVect_1 = pSourcePoly->pVerticies[index];
		
		(index==2) ? (pVect_2=pSourcePoly->pVerticies[0]) : (pVect_2=pSourcePoly->pVerticies[index+1]);
    	// evalute segment against partioning plane.
		fOrient_1 = MTPl_Evaluate( pPartition , pVect_1 );
		fOrient_2 = MTPl_Evaluate( pPartition , pVect_2 );

		// HACK!!!
//		if( fOrient_1==0 || fOrient_2==0 )return -1;
		
		// determine which ( if any ) of the vectors span the partioning plane.
		if( fOrient_1 < 0 )
		{
			rVectList[ rCount ] = pVect_2;
			rxIndicies[ 0 ] = iNumPolys;
			rxIndicies[ 1 ] = (iNumPolys==1) ? (0) : (1);

			if( fOrient_2 > 0 )
			// spanning the partioning plane from back to front
			{				
				vIntersects[iNumPolys] = MTPl_Intersect( pPartition , pSourcePoly , pVect_1 , pVect_2 );
				iNumPolys++;
			}

			rCount++;
		}

		else if( fOrient_1 > 0 )
		{
			fVectList[ fCount ] = pVect_2;
			fxIndicies[ 0 ] = iNumPolys;
			fxIndicies[ 1 ] = (iNumPolys==1) ? (0) : (1);

			if( fOrient_2 < 0 )
			// spanning the partioning plane from front to rear.
			{
				vIntersects[iNumPolys] = MTPl_Intersect( pPartition , pSourcePoly , pVect_1 , pVect_2 );
				iNumPolys++;
			}

			fCount++;
		}

	   else
	   { 
		   MessageBox( NULL , "stupid" , "Stupid" , MB_OK );
	   }
	}

	// create the new polygons.
	if( (rCount + iNumPolys) == 3 )
	{		
		pLeftChild->Polys.pPolygons[lIndex] =  new Poly_t;
		MTP_AllocTri( pLeftChild->Polys.pPolygons[lIndex ] );

		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[0] = new Vect3_t;
		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[1] = new Vect3_t;
		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[2] = new Vect3_t;

 	    pLeftChild->Polys.pPolygons[lIndex]->pVerticies[0] = rVectList[0];
       *pLeftChild->Polys.pPolygons[lIndex]->pVerticies[1] = vIntersects[fxIndicies[0]];
	   *pLeftChild->Polys.pPolygons[lIndex]->pVerticies[2] = vIntersects[fxIndicies[1]];
	    
		// don't forget to make the normal
		MTP_MakeNormal( pLeftChild->Polys.pPolygons[lIndex] );
		MTV_Normalize( pLeftChild->Polys.pPolygons[lIndex]->Normal );
	}

	else
	{
		pLeftChild->Polys.pPolygons[lIndex] = new Poly_t;
		MTP_AllocQuad( pLeftChild->Polys.pPolygons[lIndex] );

		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[0] = new Vect3_t;
		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[1] = new Vect3_t;
        pLeftChild->Polys.pPolygons[lIndex]->pVerticies[2] = new Vect3_t;
		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[3] = new Vect3_t;

		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[0] = rVectList[0];
		pLeftChild->Polys.pPolygons[lIndex]->pVerticies[1] = rVectList[1];
	   *pLeftChild->Polys.pPolygons[lIndex]->pVerticies[2] = vIntersects[fxIndicies[0]];
	   *pLeftChild->Polys.pPolygons[lIndex]->pVerticies[3] = vIntersects[fxIndicies[1]];
        
	   MTP_MakeNormal( pLeftChild->Polys.pPolygons[lIndex] );
	   MTV_Normalize( pLeftChild->Polys.pPolygons[lIndex]->Normal );
	}

	if( (fCount + iNumPolys) == 3 )
	{
		pRightChild->Polys.pPolygons[rIndex] = new Poly_t;
		MTP_AllocTri( pRightChild->Polys.pPolygons[rIndex] );

		pRightChild->Polys.pPolygons[rIndex]->pVerticies[0] = new Vect3_t;
		pRightChild->Polys.pPolygons[rIndex]->pVerticies[1] = new Vect3_t;
		pRightChild->Polys.pPolygons[rIndex]->pVerticies[2] = new Vect3_t;

	    pRightChild->Polys.pPolygons[rIndex]->pVerticies[2] = fVectList[0];
       *pRightChild->Polys.pPolygons[rIndex]->pVerticies[0] = vIntersects[rxIndicies[1]];
	   *pRightChild->Polys.pPolygons[rIndex]->pVerticies[1] = vIntersects[rxIndicies[0]];

	   MTP_MakeNormal( pRightChild->Polys.pPolygons[rIndex] );
	   MTV_Normalize( pRightChild->Polys.pPolygons[rIndex]->Normal );
	}

	else
	{
		pRightChild->Polys.pPolygons[rIndex] = new Poly_t;
		MTP_AllocQuad( pRightChild->Polys.pPolygons[rIndex] );		

		pRightChild->Polys.pPolygons[rIndex]->pVerticies[0] = new Vect3_t;
		pRightChild->Polys.pPolygons[rIndex]->pVerticies[1] = new Vect3_t;
		pRightChild->Polys.pPolygons[rIndex]->pVerticies[2] = new Vect3_t;
		pRightChild->Polys.pPolygons[rIndex]->pVerticies[3] = new Vect3_t;

		pRightChild->Polys.pPolygons[rIndex]->pVerticies[2] = fVectList[0];
		pRightChild->Polys.pPolygons[rIndex]->pVerticies[3] = fVectList[1];	   
	   *pRightChild->Polys.pPolygons[rIndex]->pVerticies[0] = vIntersects[rxIndicies[1]];
	   *pRightChild->Polys.pPolygons[rIndex]->pVerticies[1] = vIntersects[rxIndicies[0]];

	   MTP_MakeNormal( pRightChild->Polys.pPolygons[rIndex] );
	   MTV_Normalize( pRightChild->Polys.pPolygons[rIndex]->Normal );
	}
	
	// NOTE : the split polygons are to be classified as fragments, and not to be used for further partioning planes
	 pLeftChild->Polys.pPolygons[lIndex]->bspFragment = k_true;
	pRightChild->Polys.pPolygons[rIndex]->bspFragment = k_true;*/

    pLeftChild->Polys.pPolygons[lIndex] = pSourcePoly;
   pRightChild->Polys.pPolygons[rIndex] = pSourcePoly;
   
   return 0;	
}

/*
**************************************************
* R_BSP_FindSplitPlane
* Determines which polygon within the passed list 
* of polygons will serve as the optimum partioning plane.
**************************************************
*/
static int R_BSP_FindSplitPlane( pPolySet_t pList , int* front , int* behiend , int* consistent ,int* split)
{
	Plane_t tempPlane;
	int optPoly=0,currFront=0,currBehiend=0,currSplit=0,badPoly=0,currConsistent=0;
	float optComposite=9999999.0f,currComposite=0.0f;
	
	// odd case #1: null polyset list passed ( single,leaf,node )
	if(!pList->setSize)
	{
		return -1;
	}

	for(int index_01=0;index_01<pList->setSize;index_01++)
	{
		MTPl_Build( pList->pPolygons[index_01] , &tempPlane );

		for(int index_02=0;index_02<pList->setSize;index_02++)
		{
			switch( MTPl_Classify( &tempPlane , pList->pPolygons[index_02] ) )
			{
			case PPR_FRONT:
				{
					currFront++;
					break;
				}
			case PPR_BEHIEND:
				{
					currBehiend++;
					break;
				}
			case PPR_SPLIT:
				{
					currSplit++;
					break;
				}
			case PPR_CONSISTENT:
			// consider using epilison values here to create thick plane ( less polygons split.. )
				{
					currConsistent++;
					break;
				}
			}
		}
		
		currComposite = ( NODE_DETMN_SPLIT_FAC*currSplit ) + ( NODE_DETMN_BALANCE_FAC*(abs(currFront-currBehiend)) );
		
		if( currComposite < optComposite/* && (pList->pPolygons[index_01]->bspFragment == k_false)*/ )
		{
			optComposite = currComposite;
			optPoly = index_01;
			*front = currFront;
			*behiend = currBehiend;
			*consistent = currConsistent;
			*split = currSplit;
		}	
		

		// odd case #2: all polygons lie a a constant orientation.
		if( (!currFront) || (!currBehiend) )
		{
			badPoly++;
		}

		currFront=currBehiend=currSplit=currConsistent=0;
	}
	  
	if( (*front==0) || (*behiend==0) )
	{
		// ambigious convex set
		optPoly=-1;
	}
	
	return ( (badPoly==pList->setSize) ? (-1) : (optPoly) );
} 

/*
**************************************************
* R_BSP_AddPolygon
* Add the specified polygon to the specified
* bsp node. NOTE: this assumes that the passed
* polygon is to be used as a partioning plane.
**************************************************
*/
static pbspNode_t R_BSP_AddPolygon( pbspNode_t pNode , pPoly_t pPolygon )
{
	pbspNode_t walker = pNode;
	Plane_t plane;
	MTPl_Build( pPolygon , &plane );

	if( MTPl_Classify( &plane , pPolygon ) == PPR_FRONT )
	{
		if( walker->prChild )
		{
   	    	R_BSP_AddPolygon( walker->prChild , pPolygon );
		}

		
		else
		{
			walker->prChild = new bspNode_t;
			walker = pNode->prChild;
			walker->prChild = walker->plChild = NULL;

			walker->pPoly = pPolygon;
    		walker->SplitPlane = plane;
		}
	}

	else
	{
		if( walker->plChild )
		{
			R_BSP_AddPolygon( walker->plChild , pPolygon );
		}		
 
		else
		{
			walker->plChild = new bspNode_t;
			walker = pNode->plChild;
			walker->prChild = walker->plChild = NULL;

			walker->pPoly = pPolygon;
     		walker->SplitPlane = plane;
		}
	}

	return walker;
}

/*
**************************************************
* R_BSP_ConstructTree
* Builds BSP tree from the set of passed polygons.
* Note,this routine utilizes the hueristic whereby 
* only the polygons within the potential splitting
* plane's subspace are taken into consideration
* when determing sucessive splitting planes.
**************************************************
*/
void R_BSP_ConstructTree( pbspNode_t pRoot , pPolySet_t polys )
{
	
}

void R_BSP_ConstructTree( pbspNode_t pRoot )
{	
	static pbspNode_t rootNode = pRoot;
	static int called=0;
	int front=0,behiend=0,consistent=0,split=0;
	Plane_t splitPlane;
	pPolySet_t pPolys = &pRoot->Polys;

	called++;

	if( pRoot->Polys.setSize == 1 )
	{
		// consider tweaking this a bit so that the proper child recieves this.
		pRoot->type = NT_LEAF;
		pRoot->pPoly = pRoot->Polys.pPolygons[0];
		pPolys->setSize = 0;
		return;
	}

 	pRoot->bVisited = k_false;
	pRoot->visited = k_false;
	pRoot->type = NT_TREE;

	int splitter = R_BSP_FindSplitPlane( pPolys , &front , &behiend , &consistent , &split );

	if( splitter == -1 )
	// segregated polygons and convex sets are pushed here.
	{
		pRoot->type = NT_LEAF;

		// these leaves are pushed to the tree's leaves ( creating the full leave tree )		
		
		return;
	}

	MTPl_Build( pRoot->Polys.pPolygons[splitter] , &splitPlane );

	pRoot->SplitPlane = splitPlane;
	pRoot->pPoly = pRoot->Polys.pPolygons[splitter];
	
	pRoot->plChild = new bspNode_t;
	pRoot->prChild = new bspNode_t;
					 
	pRoot->plChild->plChild=pRoot->plChild->prChild=NULL;
	pRoot->prChild->plChild=pRoot->prChild->prChild=NULL;

	pRoot->plChild->Polys.setSize=behiend+split;
	pRoot->prChild->Polys.setSize=front+split;
	
	pRoot->plChild->Polys.pPolygons = new pPoly_t[ behiend+split ];
	pRoot->prChild->Polys.pPolygons = new pPoly_t[ front+split ]; 

	for(int index=0,fIndex=0,rIndex=0,cIndex=0,sIndex=0;index<pPolys->setSize;index++)
	{
		switch( MTPl_Classify( &splitPlane , pPolys->pPolygons[index] ) )
		{
		case PPR_BEHIEND:
			{
				memcpy( &pRoot->plChild->Polys.pPolygons[rIndex] , &pPolys->pPolygons[index] , sizeof(pPoly_t) );
				rIndex++;
				break;
			}
		case PPR_FRONT:
			{
				memcpy( &pRoot->prChild->Polys.pPolygons[fIndex] , &pPolys->pPolygons[index] , sizeof(pPoly_t) );
				fIndex++;
				break;
			}
		case PPR_SPLIT:
			{
       			R_BSP_SplitPolygon( pRoot->plChild , rIndex , pRoot->prChild , fIndex ,  &splitPlane , pPolys->pPolygons[index] );
				rIndex++,fIndex++;
    			break;
			}
		case PPR_CONSISTENT:
			{
				break;
			}
		}
	}

    if( pRoot != rootNode )
	{
 		delete[]pRoot->Polys.pPolygons;
	}

//	pRoot->Polys.setSize=0;

	if( pRoot->plChild->Polys.setSize )
	{
		R_BSP_ConstructTree( pRoot->plChild );
	}

	if( pRoot->prChild->Polys.setSize )
	{
		R_BSP_ConstructTree( pRoot->prChild );
	}
}
/*
****************************************************
* R_BSP_DeleteTree
* restores the memory allocated to the compilied 
* bsp tree.
*****************************************************
*/
void R_BSP_DeleteTree( pbspNode_t pRoot )
{

}

