/***********************************************
 * $author: javery
 * $date  : 28 Oct 01
 * $descp : 4-space vector definitons/routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\vector.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __MATH_VECTOR_H__
#define __MATH_VECTOR_H__

#include "util_common_h.h"

#include <math.h>
/* C interface */
typedef struct
{
	k_qword xComponent,
		    yComponent,
			zComponent,
			wComponent,
			uComponent, // NOTE u,v ordered pairs represent texure space coords.
			vComponent;
}Vect3_t,*pVect3_t,&Vect3_rt;
// Added 100602:0137 for GUI dev.
typedef struct Vect2_t
{
	float xComponent,yComponent;
}*pVect2_t;


void  MTV_Clear( Vect3_rt );
void  MTV_Negate( Vect3_rt );
void  MTV_Init( Vect3_rt , float , float , float );	
float MTV_Lenght( Vect3_rt );
void  MTV_Normalize( Vect3_rt );

// added 08 feb 02 
Vect3_t MTV_Scale( Vect3_rt , float );

float MTV_DotProd( Vect3_rt , Vect3_rt );
Vect3_t MTV_CrossProd( Vect3_rt , Vect3_rt );
Vect3_t MTV_Add( Vect3_rt , Vect3_rt , Vect3_rt );
k_boolean MTV_Equality( Vect3_rt , Vect3_rt );

/* C++ interface */
template <typename v_DT> class CVect3_t 
{
	public:
		CVect3_t( v_DT x, v_DT y, v_DT z)
        {
			Components[0] = x;
			Components[1] = y;
			Components[2] = z;
			Components[3] = 1;
		}			
			
		CVect3_t( v_DT* p_v)
		{
			Components[0] = p_v[0];
			Components[1] = p_v[1];
			Components[2] = p_v[2];
			Components[3] = 1;
		}

		~CVect3_t( void )
		{

		}

		void Clear( void )
		{
			Components[0] = 0;
			Components[1] = 0;
			Components[2] = 0;
			Components[3] = 1;
		}

		void Negate( void )
		{
			Components[0] = -Components[0];
			Components[1] = -Components[1];
			Components[2] = -Components[2];
		}

		float Lenght( void )
		{
			float rad = SQUARED(Components[0]) + SQUARED(Components[1]) + SQUARED(Components[2]);
			return (rad<0) ? (0xFFFFFFFF) : ( (float)sqrt(rad) );
		}

		void Normalize( void )
		{
			float lenght = this->Lenght();
			Components[0] /= lenght;
			Components[1] /= lenght;
			Components[2] /= lenght;
		}

		void SetMembers( v_DT x, v_DT y, v_DT z)
		{
			Components[0] = x;
			Components[1] = y;
			Components[2] = z;
			Components[3] = 1;
		}

		void SetMembers( v_DT* p_v )
		{
			Components[0] = p_v[0];
			Components[1] = p_v[1];
			Components[2] = p_v[2];
			Components[3] = 1;
		}

		float operator * ( CVect3_t& vr ) 
		{
			float dp = (this->Components[0] * vr.Components[0]) +
				       (this->Components[1] * vr.Components[1]) +
					   (this->Components[2] * vr.Components[2]);
			return dp;
		}

		CVect3_t operator % ( CVect3_t& vr)
		{
			return 
			CVect3_t<v_DT>( ( (this->Components[1]*vr.Components[2]) - (this->Components[2]*vr.Components[1]) ),
				            ( (this->Components[0]*vr.Components[2]) - (this->Components[2]*vr.Components[0]) ),
							( (this->Components[0]*vr.Components[1]) - (this->Components[1]*vr.Components[0]) ) );
		}

		CVect3_t operator + ( CVect3_t& vr )
		{
			return CVect3_t<v_DT>( (this->Components[0] + vr.Components[0]),
				                   (this->Components[1] + vr.Components[1]),
								   (this->Components[2] + vr.Components[2]) );
		}

		k_boolean operator == ( CVect3_t& vr )
		{
			if( (this->Components[0] == vr.Components[0]) &&
				(this->Components[1] == vr.Components[1]) &&
				(this->Components[2] == vr.Components[2]) )
			{
				return k_true;
			}

			else
			{
				return k_false;
			}
		}
		
		v_DT Components[ 4 ];

	private:
};


#endif
