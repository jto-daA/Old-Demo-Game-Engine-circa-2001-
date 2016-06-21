/***********************************************
 * $author: javery
 * $date  : 25 Nov 03
 * $descp : Revamped,rethought approach to depricated import_geo.cpp.
 *          close to its 2 year pathetic anniversery
 * $path  : D:\Program Files\Microsoft Visual Studio\MyProjects\KaosEngineWorking\import_3ds.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "import_3ds.h"
#include <stdio.h>











static void Import3DSObject( pModel_t pModel , FILE* p3DS_BinFile )
// the workhorse!!!!
{
	
}

int Import3DSObject( pModel_t pModel , char* sFileName )
{
	FILE* handle = fopen( sFileName , "r" );

	if( handle == NULL ) 
	{
		MessageBox( NULL , "Unable to find a required object file!!!","IG_3DS_LoadObject critical fault." , MB_OK | MB_ICONERROR );
		PostQuitMessage(0);
		return -1;
	}

	else
	{
		Import3DSObject( pModel , handle );
		fclose( handle );
	}

	return 1;
}


