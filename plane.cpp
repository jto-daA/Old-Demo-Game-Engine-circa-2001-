/***********************************************
 * $author: javery
 * $date  : 09 Dec 01
 * $descp : routines/data stuctures for plane manip.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\plane.h
 * $ver   : 0.0.0
 ***********************************************/

#include "plane.h"
#include "polygon.h"

#include <stdio.h>

void MTPl_Build( pPoly_t pPoly , pPlane_t pPlane )
{
	pPlane->Normal = MTP_MakeNormal( pPoly );
	
	if( !PLY_FLG_TYPE(pPoly->PolyFlag) )
	{
		pPlane->vVerticies[0] = *pPoly->pVerticies[0];
		pPlane->vVerticies[1] = *pPoly->pVerticies[1];
		pPlane->vVerticies[2] = *pPoly->pVerticies[2];
	}

	else
	{
		pPlane->vVerticies[0] = *pPoly->pVerticies[0];
		pPlane->vVerticies[1] = *pPoly->pVerticies[1];
		pPlane->vVerticies[2] = *pPoly->pVerticies[2];
		pPlane->vVerticies[3] = *pPoly->pVerticies[3];
	}
	
	pPlane->distance = 
    -((pPlane->Normal.xComponent*pPlane->vVerticies[0].xComponent)+
	  (pPlane->Normal.yComponent*pPlane->vVerticies[0].yComponent)+
	  (pPlane->Normal.zComponent*pPlane->vVerticies[0].zComponent));
}

/*
****************************************************
* MTPl_Paramertize
* returns the coefficents of std form of plane eqn;
* with p.D == v->w ( Ax + Bx + Cx + D )
****************************************************
*/
Vect3_t MTPl_Paramatize( pPlane_t pPlane )
{
	Vect3_t params;
	params.xComponent = pPlane->Normal.xComponent;
	params.yComponent = pPlane->Normal.yComponent;
	params.zComponent = pPlane->Normal.zComponent;
	params.wComponent = pPlane->distance;
	return params;
}

/*
*****************************************************
* MTPl_Evaluate
* evalues the value of the planes eqn for the passed
* vector; 
*****************************************************
*/
float MTPl_Evaluate( pPlane_t p , pVect3_t v3d )
{
	return (p->Normal.xComponent*v3d->xComponent+
		    p->Normal.yComponent*v3d->yComponent+
			p->Normal.zComponent*v3d->zComponent+
			p->distance);
}

/*
******************************************************
* MTPl_Classify
* spatialy classifies the passed polygon in relation to 
* the passed plane.
*******************************************************
*/
Polygon_PlaneRel MTPl_Classify( pPlane_t p , pPoly_t poly )
{
	if( !PLY_FLG_TYPE(poly->PolyFlag) )
	{
		if( (MTPl_Evaluate( p , poly->pVerticies[0] ) > 0 ) && 
		    (MTPl_Evaluate( p , poly->pVerticies[1] ) > 0 ) &&
		    (MTPl_Evaluate( p , poly->pVerticies[2] ) > 0 ) )
		{
			return PPR_FRONT;
		}

	    else if
 	    ( (MTPl_Evaluate( p , poly->pVerticies[0] ) < 0 ) && 
		  (MTPl_Evaluate( p , poly->pVerticies[1] ) < 0 ) &&
		  (MTPl_Evaluate( p , poly->pVerticies[2] ) < 0 ) )
		{
			return PPR_BEHIEND;
		}

	    else if
		( (!MTPl_Evaluate( p , poly->pVerticies[0] ))  && 
		  (!MTPl_Evaluate( p , poly->pVerticies[1] )) &&
		  (!MTPl_Evaluate( p , poly->pVerticies[2] )) )
		{
			return PPR_CONSISTENT;
		}
		
		else
		{
			return PPR_SPLIT;
		}
	}

	else
	{
		if( (MTPl_Evaluate( p , poly->pVerticies[0] ) > 0 ) &&
			(MTPl_Evaluate( p , poly->pVerticies[1] ) > 0 ) &&
			(MTPl_Evaluate( p , poly->pVerticies[2] ) > 0 ) &&
			(MTPl_Evaluate( p , poly->pVerticies[3] ) > 0 ) )
		{
			return PPR_FRONT;
		}

		else if
		( (MTPl_Evaluate( p , poly->pVerticies[0] ) < 0 ) &&
		  (MTPl_Evaluate( p , poly->pVerticies[1] ) < 0 ) &&
		  (MTPl_Evaluate( p , poly->pVerticies[2] ) < 0 ) &&
		  (MTPl_Evaluate( p , poly->pVerticies[3] ) < 0 ) )
		{
			return PPR_BEHIEND;
		}

		else if
		( (!MTPl_Evaluate( p , poly->pVerticies[0] )) &&
		  (!MTPl_Evaluate( p , poly->pVerticies[1] )) &&
		  (!MTPl_Evaluate( p , poly->pVerticies[2] )) &&
		  (!MTPl_Evaluate( p , poly->pVerticies[3] )) )
		{
			return PPR_CONSISTENT;
		}

		else
		{
			return PPR_SPLIT;
		}
	}
}

/*
****************************************************
* MTPl_Intersect
* Returns the point of intersection ( if it exsists ) 
* between the passed plane and polygon.
****************************************************
*/
Vect3_t MTPl_Intersect( pPlane_t pPlane , pPoly_t pPoly , pVect3_t pInt_1 , pVect3_t pInt_2 )
{
	float t=0,numerator=0,denomenator=0,
		  normX=pPlane->Normal.xComponent,
		  normY=pPlane->Normal.yComponent,
		  normZ=pPlane->Normal.zComponent,
		  deltaX=pInt_2->xComponent - pInt_1->xComponent,
		  deltaY=pInt_2->yComponent - pInt_1->yComponent,
		  deltaZ=pInt_2->zComponent - pInt_1->zComponent,
		  tempX=pPlane->vVerticies[0].xComponent-pInt_1->xComponent,
		  tempY=pPlane->vVerticies[0].yComponent-pInt_1->yComponent,
		  tempZ=pPlane->vVerticies[0].zComponent-pInt_1->zComponent;

	Vect3_t vIntersection;
	//
	// plane polygon intersection eqn
	//               Ax + By + Cz + D
	//  t = ------------------------------------
	//      A(delta x) + B(delta y) + C(delta z)
	//
	//  vector_component_int = vector_component_0 + t(delta_vector_exponent)

//	numerator = MTPl_Evaluate( pPlane , pInt_1 );
      numerator = (normX*tempX)+(normY*tempY)+(normZ*tempZ);
	denomenator = (normX*deltaX)+(normY*deltaY)+(normZ*deltaZ);

	if(denomenator){t = numerator/denomenator;}	else{t=0.0f;}

	MTV_Init( vIntersection , (((t*(deltaX)) + (pInt_1->xComponent))) , 
		                      (((t*(deltaY)) + (pInt_1->yComponent))) , 
							  (((t*(deltaZ)) + (pInt_1->zComponent))) );
    return vIntersection;
}


