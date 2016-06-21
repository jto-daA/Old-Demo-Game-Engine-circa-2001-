/***********************************************
 * $author: javery
 * $date  : 27 Oct 01
 * $descp : routines to handle byte order conventions
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\util_common_h.h
 * $ver   : 0.0.0
 ***********************************************/


#ifndef __UTIL_COMMON_H__
#define __UTIL_COMMON_H__

#define K32_UTIL_DT_SIZE_BYTE  1
#define K32_UTIL_DT_SIZE_WORD  2
#define K32_UTIL_DT_SIZE_DWORD 4
#define K32_UTIL_DT_SIZE_QWORD 8

#define K32_DEBUG_v_0

typedef unsigned char  k_byte;
typedef unsigned short k_word;
typedef unsigned int   k_dword;
typedef float k_qword;
typedef enum
{
	k_false, 
    k_true
}k_boolean;

#endif  /* __UTIL_COMMON_H__ */