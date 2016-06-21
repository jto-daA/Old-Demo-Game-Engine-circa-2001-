/***********************************************
 * $author: javery
 * $date  : 30 May 02
 * $descp : Routines to render scalable fonts (thanks to NeHe GL site )
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\text.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __TEXT_H__
#define __TEXT_H__

#include <windows.h>

#include "util_common_h.h"

HFONT Txt_wglBuildFont( char* , int , int , int , HDC );
int Txt_wglPrint( char* , float , float , float );

#endif 


