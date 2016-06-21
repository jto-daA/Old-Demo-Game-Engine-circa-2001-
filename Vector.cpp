/***********************************************
 * $author: javery
 * $date  : 27 Oct 01
 * $descp : 4-space vector definitons/routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\vector.h
 * $ver   : 0.0.0
 ***********************************************/

#include "vector.h"
#include "mth_common.h"
#include "util_common_h.h"

#include <math.h>
/*
**************************************************
* MTV_Clear 
* sets all vector componet to a cleared state.
**************************************************
*/
void MTV_Clear( Vect3_rt v3d )
{
	v3d.xComponent =  v3d.yComponent = v3d.zComponent = 0;
	v3d.wComponent = 1;
}
/*
**************************************************
* MTV_Negate
* Sets all realative components to their inverse
**************************************************
*/
void MTV_Negate( Vect3_rt v3d )
{
	v3d.xComponent = -v3d.xComponent;
	v3d.yComponent = -v3d.yComponent;
	v3d.zComponent = -v3d.zComponent;
}
/*
*************************************************
* MTV_Init
* Initailizes the specified vector with the passed
* values.
**************************************************
*/
void MTV_Init( Vect3_rt v3d , float x , float y , float z )
{
	v3d.xComponent = x;
	v3d.yComponent = y;
	v3d.zComponent = z;
	v3d.wComponent = 1;
	v3d.uComponent = 0;
	v3d.vComponent = 0;
}
/*
**************************************************
* MTV_Lenght
* Returns the lenght of the passed vector.
**************************************************
*/
float MTV_Lenght( Vect3_rt v3d )
{
	float radican = SQUARED(v3d.xComponent) + SQUARED(v3d.yComponent) + SQUARED(v3d.zComponent);
	
	return (( radican < 0 ) ? ( 0xFFFFFFFF ) : ( (float)sqrt( radican ) ) );

}
/*
**************************************************
* MTV_Normalize
* Normalizes the specified vector instance.
**************************************************
*/
void MTV_Normalize( Vect3_rt v3d )
{
	float lenght = MTV_Lenght( v3d );
	
	v3d.xComponent /= lenght;
	v3d.yComponent /= lenght;
	v3d.zComponent /= lenght;
}
/*
***************************************************
* MTV_DotProd
* Returns the angle between two 3-space vectors
***************************************************
*/
float MTV_DotProd( Vect3_rt v3d_01 , Vect3_rt v3d_02 )
{
	return
    (
	  
	  ( v3d_01.xComponent * v3d_02.xComponent ) +
	  ( v3d_01.yComponent * v3d_02.yComponent ) +
	  ( v3d_01.zComponent * v3d_02.zComponent )
	);
}
/*
***************************************************
* MTV_CrossProd
* Returns a vector perpendicular to the two passed
* vectors.
***************************************************
*/
Vect3_t MTV_CrossProd( Vect3_rt v_01 , Vect3_rt v_02 )
{
	Vect3_t v_Return;

	MTV_Init((v_Return) , 
		     (( v_01.yComponent * v_02.zComponent )-( v_01.zComponent * v_02.yComponent )),
			 (( v_01.xComponent * v_02.zComponent )-( v_01.zComponent * v_02.xComponent )),
			 (( v_01.xComponent * v_02.yComponent )-( v_01.yComponent * v_02.xComponent )) );

	return v_Return;
}
/*
****************************************************
* MTV_Add
* Computes the sum of the two passed vectors.
****************************************************
*/
Vect3_t MTV_Add( Vect3_rt v_01 , Vect3_rt v_02 , Vect3_rt v_r )
{
	Vect3_t v_Ret;
	
	MTV_Init( v_r , ( v_01.xComponent + v_02.xComponent ) ,
                    ( v_01.yComponent + v_02.yComponent ) ,
					( v_01.zComponent + v_02.zComponent ) );

	v_Ret = v_r;

	return v_Ret;
}
/*
*****************************************************
* MTV_Equality
* Determines if the two passed vectors are equal.
*****************************************************
*/
k_boolean MTV_Equality( Vect3_t v_0 , Vect3_t v_1 )
{
	if( ( v_0.xComponent == v_1.xComponent ) &&
		( v_0.yComponent == v_1.yComponent ) &&
		( v_0.zComponent == v_1.zComponent ) )
	{
		return k_true;
	}

	else
	{
		return k_false;
	}
}


Vect3_t MTV_Scale( Vect3_rt v , float s )
{
	Vect3_t rv;
	MTV_Init( rv , v.xComponent*s , v.yComponent*s , v.zComponent*s );
	return rv;
}


