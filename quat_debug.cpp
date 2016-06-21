// debugging the quaternions 09 feb 03
#include "required.h"
#include "vector.h"
#include "quaternion.h"

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLineArgs , int iWinArg )
{
	Q q1,q2,qsum;
	float mag;

	MTQ_Init( &q1 , 0 , 0 , 0 , 1 ); 
	MTQ_Init( &q2 , 0 , 0 , 0 , 2 );

	qsum = MTQ_Multiply( &q1 , &q2 );

	MTQ_Normalize( &qsum );


	mag = MTQ_Lenght( &qsum );




	return 1;
}

