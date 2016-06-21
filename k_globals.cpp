/***********************************************
 * $author: javery
 * $date  : 24 May 02 
 * $descp : variables visible throughout engine
 *          COM interface(s/ing).
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\global.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "OpenGL.h"
#include "Win32.h"

#include <windows.h>
#include <dinput.h>
#include <dsound.h>

WndStruct wndStruct;
HINSTANCE hInstance=NULL;
k_byte di_KeyboardBuffer[256];
DIMOUSESTATE di_MouseState;