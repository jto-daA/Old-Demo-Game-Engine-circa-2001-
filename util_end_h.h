/***********************************************
 * $author: javery
 * $date  : 27 Oct 01
 * $descp : routines to handle byte order conventions
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\util_end.cpp
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __UTIL_ENDIAN_H__
#define __UTIL_ENDIAN_H__

#include "util_common_h.h"

#include <windows.h>
#include <stdio.h>

template <typename T > T UTL_ReverseEndian( T gn_Value )
{
	int dt_Size = sizeof( gn_Value ); 
	T gn_ReturnValue = 0;

	switch( dt_Size )
	{
	case K32_UTIL_DT_SIZE_BYTE:
		{
			k_byte low_Nybble = (( gn_Value ) & ( 0x0F ) ), 
				  high_Nybble = (( gn_Value ) & ( 0xF0 ) );   
			
			low_Nybble <<= 4;
			high_Nybble >>= 4;

			gn_ReturnValue = low_Nybble | high_Nybble;

			break;
		}

	case K32_UTIL_DT_SIZE_WORD:
		{
			k_word low_Word = (( gn_Value ) & ( 0x00FF ) ),
				  high_Word = (( gn_Value ) & ( 0xFF00 ) );
			
			low_Word <<= 8;
			high_Word >>= 8;

			gn_ReturnValue = low_Word | high_Word;

			break;
		}

	case K32_UTIL_DT_SIZE_DWORD:
		{
			k_dword low_Word = (( gn_Value ) & ( 0x0000FFFF ) ),
  				   high_Word = (( gn_Value ) & ( 0xFFFF0000 ) );
 
			low_Word <<= 16;
		   high_Word >>= 16;
		   
		   gn_ReturnValue = low_Word | high_Word;

		   break;
		}
	
	default:
		{
		//	MessageBox( NULL , "Invalid data type size for endian toggle." , "UTL_ReverseEndian fault" , MB_EXCLAMATION | MB_OK );
			return -1;
		}
	}

	return gn_ReturnValue;
}

k_byte  UTL_SwitchEndian_ReadByteFromFile( FILE* , long );
k_word  UTL_SwitchEndian_ReadWordFromFile( FILE* , long );
k_word  UTL_SwitchEndian_ReadWordFromFile( FILE* );
k_dword UTL_SwitchEndian_ReadDWordFromFile( FILE* , long  );
k_dword UTL_SwitchEndian_ReadDWordFromFile( FILE* );

#endif /* __UTIL_ENDIAN_H__ */
