/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Polygon data structure/supporting routines
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Polygon.h
 * $ver   : 0.0.0
 * $mods  : javery | 6 mar 02 : Removed rFront/rBack members from Poly_t       
 ***********************************************/

#ifndef __MATH_POLYGON_H__
#define __MATH_POLYGON_H__

#include "vector.h"
#include "util_common_h.h"

/* This is a pretty neato way of combining and extracting poly data; will add more later */
#define PLY_FLG_TYPE(flg)         ((flg) & (0xFFFE))
#define PLY_FLG_VISIBLE(flg)      ((flg) & (0xFFFD))
#define PLY_FLG_BSPC(flg)         ((flg) & (0xFFFC))
#define PLY_FLG_BSPR(flg)         ((flg) & (0xFFFB))
#define PT_TRIANGULAR       0x0001
#define PT_QUADRANGULAR     0x0000

typedef struct Poly_t
{
	pVect3_t* pVerticies;
	k_word PolyFlag;
	Vect3_t Normal;
	k_boolean bspNode,bspFragment;
}*pPoly_t,&Poly_rt;

typedef struct PolySet_t
{
	pPoly_t* pPolygons;
	k_word setSize;
}*pPolySet_t;

void MTP_AllocTri( pPoly_t );
void MTP_AllocQuad( pPoly_t );
void __inline MTP_SetVisible( pPoly_t );
void __inline MTP_ClearVisible( pPoly_t );
void __inline MTP_SetType( pPoly_t );    /* the default type for a polygon is ( ofcourse ) triangular */
void __inline MTP_ClearType( pPoly_t );
Vect3_t MTP_MakeNormal( pPoly_t );
k_boolean MTP_IsVisible( pPoly_t , Vect3_rt );
pPoly_t MTP_AddPolygon( pPolySet_t , pPoly_t );

#endif /* __MATH_POLYGON_H__ */
