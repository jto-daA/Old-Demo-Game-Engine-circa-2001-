/***********************************************
 * $author: javery
 * $date  : 27 Oct 01
 * $descp : routines to handle byte order conventions
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\util_end_h.h
 * $ver   : 0.0.0
 ***********************************************/

#include "util_end_h.h"
#include "util_common_h.h"

#include <stdio.h>

/*
**********************************************************
* UTL_SwitchEndian_ReadByteFromFile
* Reads a byte from a file ( at the specified offset ), 
* and returns the result in the opposite byte order.
**********************************************************
*/
k_byte UTL_SwitchEndian_ReadByteFromFile( FILE *pfFile , long lFileOffset )
{
	fseek( pfFile , lFileOffset , SEEK_SET );
	k_byte bFileRead = fgetc( pfFile );

	return UTL_ReverseEndian<k_byte>( bFileRead );	
}
/*
**********************************************************
* UTL_SwitchEndian_ReadWordFromFile
* "" word from a file "".
**********************************************************
*/
k_word UTL_SwitchEndian_ReadWordFromFile( FILE *pfFile , long lFileOffset )
{
	fseek( pfFile , lFileOffset , SEEK_SET);

	k_word low_Word = fgetc( pfFile ),
	      high_Word = fgetc( pfFile );

	low_Word <<=  8;

	k_word wReturnValue = low_Word | high_Word;
   
   return UTL_ReverseEndian< k_word >( wReturnValue );
}

// preserves file pointer
k_word UTL_SwitchEndian_ReadWordFromFile( FILE* pfFile )
{
	k_word low_Word = fgetc( pfFile ),
          high_Word = fgetc( pfFile );

	low_Word <<=  8;

	k_word wReturnValue = low_Word | high_Word;
   
   return UTL_ReverseEndian< k_word >( wReturnValue );
}
/*
**********************************************************
* UTL_SwitchEndian_ReadDWordFromFile
* "" word from a file "".
**********************************************************
*/
k_dword UTL_SwitchEndian_ReadDWordFromFile( FILE *pfFile ,  long lFileOffset )
{
	fseek( pfFile , lFileOffset , SEEK_SET );

	int lowWord=UTL_SwitchEndian_ReadWordFromFile( pfFile ),
		 hiWord=UTL_SwitchEndian_ReadWordFromFile( pfFile );
	int returnValue=0;

	lowWord <<= 16;

    returnValue = lowWord | hiWord;
	return UTL_ReverseEndian<k_dword>( returnValue );
}

//preservers file pointer.
k_dword UTL_SwitchEndian_ReadDWordFromFile( FILE* pf )
{
	int lowWord=UTL_SwitchEndian_ReadWordFromFile( pf ),
		 hiWord=UTL_SwitchEndian_ReadWordFromFile( pf );
	
    lowWord <<= 16;

	return (lowWord|hiWord);
}

