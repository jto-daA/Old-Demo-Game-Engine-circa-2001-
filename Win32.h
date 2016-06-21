/***********************************************
 * $author: javery
 * $date  : 13 Nov 01
 * $descp : Win32 OS interface
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Win32.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __SYS_WIN32_H__
#define __SYS_WIN32_H__

#include "util_common_h.h"

#include <windows.h>

typedef struct
{
	HWND hWnd;
	WNDCLASS wndClass	;
	k_word xDimension,yDimension;
	DWORD wStyle,wExStyle;
	HINSTANCE hInstance;
	char* sWindowCaption;
}WndStruct,*pWndStruct;

void SYS_W32_RegisterClass( pWndStruct );
void SYS_W32_CreateWindow( pWndStruct );
LRESULT CALLBACK SYS_32_WndProc( HWND , UINT , WPARAM , LPARAM );

#endif /* __SYS_WIN32_H__ */
