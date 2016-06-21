/***********************************************
 * $author: javery
 * $date  : 09 Dec 01
 * $descp : routines/data stuctures for plane manip.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\plane.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __MATH_PLANE_H__
#define __MATH_PLANE_H__

#include "vector.h"
#include "polygon.h"

#define MTPL_DEFAULT_EPSILON 50.0f

typedef struct Plane_t
{
	Vect3_t vVerticies[3],Normal;
	float distance;
}*pPlane_t;

enum Vector_PlaneRel
{
	PVR_CONSISTENT,
    PVR_FRONT,
	PVR_BEHIEND
}; 

enum Polygon_PlaneRel
{
	PPR_CONSISTENT,
    PPR_FRONT,
	PPR_BEHIEND,
	PPR_SPLIT
};

void MTPl_Build( pPoly_t , pPlane_t );
Vect3_t MTPl_Paramatize( pPlane_t );
float MTPl_Evaluate( pPlane_t , pVect3_t );
Polygon_PlaneRel MTPl_Classify( pPlane_t , pPoly_t );
Vect3_t MTPl_Intersect( pPlane_t , pPoly_t , pVect3_t , pVect3_t );

#endif /* __MATH_PLANE_H__ */