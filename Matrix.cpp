/***********************************************
 * $author: javery
 * $date  : 30 Oct 01
 * $descp : Matrix definitons/routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Matrix.h
 * $ver   : 0.0.0
 ***********************************************/

#include "util_common_h.h"
#include "mth_common.h"
#include "vector.h"
#include "matrix.h"

#include <memory.h>
#include <windows.h>
#include <gl/gl.h>

void MTM_LoadIdentity( Matrix_t m )
{
	memset( m , 0 , sizeof(float)*16 );
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1 ;
}

void MTM_Normalize( Matrix_t m )
{
	Vect3_t r_1,r_2,r_3,r_4;
		
	MTV_Init( r_1 , m[0][0] , m[0][1] , m[0][2] );
	MTV_Init( r_2 , m[1][0] , m[1][1] , m[1][2] );
	MTV_Init( r_3 , m[2][0] , m[2][1] , m[2][2] );
	MTV_Init( r_4 , m[3][0] , m[3][1] , m[3][2] );

    MTV_Normalize( r_1 ); 
	MTV_Normalize( r_2 );
	MTV_Normalize( r_3 );
	MTV_Normalize( r_4 );

	m[0][0] = r_1.xComponent;
	m[0][1] = r_1.yComponent;
	m[0][2] = r_1.zComponent;
	m[0][3] = r_1.wComponent;

	m[1][0] = r_2.xComponent;
	m[1][1] = r_2.yComponent;
	m[1][2] = r_2.zComponent;
	m[1][3] = r_2.wComponent;

	m[2][0] = r_3.xComponent;
	m[2][1] = r_3.yComponent;
	m[2][2] = r_3.zComponent;
	m[2][3] = r_3.wComponent;

	m[3][0] = r_4.xComponent;
	m[3][1] = r_4.yComponent;
	m[3][2] = r_4.zComponent;
	m[3][3] = r_4.wComponent;
}

void MTM_Scale( Matrix_t m , float f_sxyz )
{
	for(int row = 0;row < 4; row++)
	{
		for( int col = 0;col < 4; col++)
		m[row][col] *= f_sxyz;
	}
}

void MTM_ScalDiag( Matrix_t m , float f_ds )
{
	m[0][0] *= f_ds;
	m[1][1] *= f_ds;
	m[2][2] *= f_ds;
	m[3][3] *= f_ds;
}

void MTM_SetTranslation( Matrix_t m , float x , float y , float z )
{
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void MTM_SetTranslation( Matrix_t m , Vect3_t v )
{
	m[0][3] = v.xComponent;
	m[1][3] = v.yComponent;
	m[2][3] = v.zComponent;
}

void MTM_SetRotation( Matrix_t m , float a , float x , float y , float z )
{
	/* I suppose I should let openGL handle the rotations */
	glMatrixMode( GL_MODELVIEW );
    glRotatef( a , x , y , z );
}

void MTM_SetRotation( Matrix_t m , float f_Angle , Vect3_t v )
{
   glMatrixMode( GL_MODELVIEW );
   glRotatef( f_Angle , v.xComponent , v.yComponent , v.zComponent );
}

void MTM_Multiply( Matrix_t m_0 , Matrix_t m_1 , Matrix_t m_r )
{
	for(int row = 0;row < 4;row++)
	{
		for(int col = 0;col < 4;col++)
		{
			float fTemp = 0;
			
			for(int in = 0;in < 4;in++)
			{
				fTemp += ( m_0[row][in] * m_1[in][col] );
			}

			m_r[row][col] = fTemp;
		}

	}
}

Vect3_t MTM_Multiply( Matrix_t m , Vect3_rt v )
{
	Vect3_t v_Resultant=v;
	
	v_Resultant.xComponent = ( ( v.xComponent ) * ( m[0][0] ) ) +
		                     ( ( v.yComponent ) * ( m[0][1] ) ) +
							 ( ( v.zComponent ) * ( m[0][2] ) ) +
							 ( ( v.wComponent ) * ( m[0][3] ) ) ;

	v_Resultant.yComponent = ( ( v.xComponent ) * ( m[1][0] ) ) +
		                     ( ( v.yComponent ) * ( m[1][1] ) ) +
							 ( ( v.zComponent ) * ( m[1][2] ) ) +
							 ( ( v.wComponent ) * ( m[1][3] ) ) ;


	v_Resultant.zComponent = ( ( v.xComponent ) * ( m[2][0] ) ) +
		                     ( ( v.yComponent ) * ( m[2][1] ) ) +
							 ( ( v.zComponent ) * ( m[2][2] ) ) +
							 ( ( v.wComponent ) * ( m[2][3] ) ) ;


	v_Resultant.wComponent = ( ( v.xComponent ) * ( m[3][0] ) ) +
		                     ( ( v.yComponent ) * ( m[3][1] ) ) +
							 ( ( v.zComponent ) * ( m[3][2] ) ) +
							 ( ( v.wComponent ) * ( m[3][3] ) ) ;

	return v_Resultant;
}

void MTM_Switch_oglFormat( Matrix_t m )
{
	for(int row = 0;row<4;row++)
	{
		for( int col = 0;col < 4;col++)
		m[row][col] = m[col][row];
	}
}



	


