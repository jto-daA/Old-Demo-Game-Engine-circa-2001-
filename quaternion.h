/***********************************************
 * $author: javery
 * $date  : 08 Feb 03
 * $descp : fun with quaternions. 
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\quaternion.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __MTH_QUATERNION_H__
#define __MTH_QUATERNION_H__

#include "util_common_h.h"
#include "matrix.h"
#include "vector.h"

typedef struct Quaternion_t
{ 
	struct Vect3i_t
	{ 
		float i,j,k;
	};

	float s;
	Vect3i_t v;
}Quat_t,Q,*pQuaternion_t,*pQuat_t;

void MTQ_Init( Quaternion_t* , float , float , float , float ); 
void MTQ_Init( Quaternion_t* , float  , Vect3_t );
Vect3_t MTQ_Convert( Quaternion_t* );
Quaternion_t MTQ_Conjugate( Quaternion_t* );
Quaternion_t MTQ_Add( Quaternion_t* , Quaternion_t* );
Quaternion_t MTQ_Multiply( Quaternion_t* , Quaternion_t* );
float MTQ_Lenght( Quaternion_t* );
void MTQ_Clear( Quaternion_t* );
void MTQ_Negate( Quaternion_t* );
void MTQ_Normalize( Quaternion_t* );



#endif 
