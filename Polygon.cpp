/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Polygon data structure/supporting routines
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Polygon.h
 * $ver   : 0.0.0
 ***********************************************/

#include "vector.h"
#include "polygon.h"
#include "util_common_h.h"

#include <memory.h>

void MTP_AllocTri( pPoly_t p )
{
	p->pVerticies = new Vect3_t*[ 3 ];
	p->bspNode = k_false;
	p->bspFragment = k_false;
	p->PolyFlag = PT_TRIANGULAR;
}

void MTP_AllocQuad( pPoly_t p )
{
	p->pVerticies = new Vect3_t*[ 4 ];
	p->bspNode = k_false;
	p->bspFragment = k_false;
	p->PolyFlag = PT_QUADRANGULAR;
}

void __inline MTP_SetVisible( pPoly_t p )
{
    p->PolyFlag |= 0x0001;
}

void __inline MTP_ClearVisible( pPoly_t p )
{
	p->PolyFlag |= 0x0000;
}

void __inline MTP_SetType( pPoly_t p )
{
	p->PolyFlag |= 0x0002;
}

Vect3_t MTP_MakeNormal( pPoly_t  p )
/* this relies on the age-old atage of consistent vector placement, be it  CW/CCW ) */
{
	Vect3_t thisNormal; 
	int a = PLY_FLG_TYPE(p->PolyFlag);
	
	if( !PLY_FLG_TYPE( p->PolyFlag ) )
	{
    	thisNormal = MTV_CrossProd( *(p->pVerticies[0]) , *(p->pVerticies[2]) );
	}

	else
	{
		thisNormal = MTV_CrossProd( *(p->pVerticies[0]) , *(p->pVerticies[3]) );
	}

	p->Normal = thisNormal;

	return p->Normal;
}

/*
***************************************************
* MTP_IsVisible
* Determines if the passed polygon is visible
* from the specified vantage point.
***************************************************
*/
k_boolean MTP_IsVisible( pPoly_t p , Vect3_rt v )
{
	return ( MTV_DotProd( p->Normal , v ) < 0 ) ?
	( k_false ) : ( k_true );
}

pPoly_t MTP_AddPolygon( pPolySet_t pset , pPoly_t poly )
{
	return (pPoly_t)(0);
}
