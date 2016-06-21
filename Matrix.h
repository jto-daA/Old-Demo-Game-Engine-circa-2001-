/***********************************************
 * $author: javery
 * $date  : 30 Oct 01
 * $descp : Matrix definitons/routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Matrix.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __MATH_MATRIX_H__
#define __MATH_MATRIX_H__

#include "util_common_h.h"
#include "mth_common.h"
#include "vector.h"

typedef k_qword Matrix_t [4][4];

/* C  interface */
void MTM_LoadIdentity( Matrix_t);
void MTM_Normalize( Matrix_t);
void MTM_Scale( Matrix_t , float );
void MTM_ScaleDiag( Matrix_t , float );
void MTM_SetTranslation( Matrix_t, float , float ,float );
void MTM_SetTranslation( Matrix_t, Vect3_t );
void MTM_SetRotation( Matrix_t, float , float , float , float );
void MTM_SetRotation( Matrix_t, float , Vect3_rt );
void MTM_Multiply( Matrix_t, Matrix_t, Matrix_t);
Vect3_t MTM_Multiply( Matrix_t, Vect3_rt );
void MTM_Switch_oglFormat( Matrix_t);

/* C++ interface */
template <typename m_DT>class CMatrix_t
{
public:
	CMatrix_t( void )
	{
		LoadIdentity();
	}

	CMatrix_t( m_DT d ) 
    {
		LoadIdentity();
		Data[0][0] = Data[1][1] = Data[2][2] = Data[3][3] = d;
	}

	~CMatrix_t( void )
	{

	}

	void LoadIdentity( void ) 
	{
		memset( Data , 0 , sizeof(m_DT)*16 );
		Data[0][0] = Data[1][1] = Data[2][2] = Data[3][3] = 1;
	}

	void SetTranslation( m_DT x , m_DT , m_DT );
	void SetRotation( m_DT , m_DT , m_DT , m_DT );
	void Switch_oglFormat( void );

	CMatrix_t operator * ( CMatrix_t );
	/* Hmmm... This is a rather unsophisticated thing to have.... */
	CVect3_t<m_DT> operator * ( CVect3_t<m_DT> );

	m_DT Data[4][4];
private:
	Vect3_t v_Displacement,v_Rotation,vw_Scale;
};

#endif /* __MATH_MATRIX_H__ */



