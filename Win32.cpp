/***********************************************
 * $author: javery
 * $date  : 13 Nov 01
 * $descp : Win32 OS interface
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Win32.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "win32.h"
#include "opengl.h"
#include <windows.h>

/*
*******************************************
* W32_WndProc
* Handles messages sent to and generated by the
* applicaitons main window.
*******************************************
*/
LRESULT CALLBACK SYS_W32_WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{	
	HDC hDC;
	PAINTSTRUCT painter;

	switch( uMsg )
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	case WM_QUIT:
		{
			PostQuitMessage(0);
			return 0;
		}

	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

	case WM_PAINT:
		{
			hDC = BeginPaint( hWnd , &painter );
			EndPaint( hWnd , &painter );
			break;
		}

	case WM_SIZE:
		{
			SYS_OGL_ResizeContext( LOWORD( lParam ) , HIWORD( lParam ) );
			break;
		}

	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );	
}

/*
*******************************************
* SYS_W32_RegisterClass
* Registers the passed class
*******************************************
*/
void SYS_W32_RegisterClass( pWndStruct pWS )
{
	pWS->wndClass.cbClsExtra = 0;
	pWS->wndClass.cbWndExtra = 0;
	pWS->wndClass.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	pWS->wndClass.hCursor = LoadCursor( NULL , IDC_ARROW );
	pWS->wndClass.hIcon   = LoadIcon( NULL , IDI_APPLICATION );
	pWS->wndClass.hInstance = pWS->hInstance;
	pWS->wndClass.lpfnWndProc = SYS_W32_WndProc;
	pWS->wndClass.lpszClassName = "Kaos Demo engine ( v 0.0.0 ) test app";
	pWS->wndClass.lpszMenuName = NULL;
	pWS->wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	RegisterClass( &pWS->wndClass );
}

/*
*******************************************
* SYS_W32_CreateWindow
* Creates the application's parent window.
*******************************************
*/
void SYS_W32_CreateWindow( pWndStruct pWS )
{
	pWS->hWnd = CreateWindowEx(/*WS_EX_TOPMOST*/pWS->wExStyle,
		                       pWS->wndClass.lpszClassName,
		                       "Kaos Demo Engine (v0.0.0) Test Application",
							   WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | pWS->wStyle,
     						   CW_USEDEFAULT,
							   CW_USEDEFAULT,
							   pWS->xDimension,
							   pWS->yDimension,
							   NULL,
							   NULL,
							   pWS->hInstance,
							   NULL );

	ShowWindow( pWS->hWnd , SW_SHOW );
	SetForegroundWindow( pWS->hWnd );
	SetFocus( pWS->hWnd );
}

