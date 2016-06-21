/***********************************************
 * $author: javery
 * $date  : 24 May 02 
 * $descp : Wrapper routines/structs to initalize DirectX
 *          COM interface(s/ing).
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\DxWrapper.h
 * $ver   : 0.0.0
 ***********************************************/

#include "Win32.h"
#include "DXWrapper.h"

#include <windows.h>
#include <dinput.h>
#include <dsound.h>

//globals
extern HINSTANCE hInstance;
extern WndStruct wndStruct;
extern k_byte di_KeyboardBuffer[256];
extern DIMOUSESTATE di_MouseState;

static LPDIRECTINPUT lpdi=NULL;
static LPDIRECTSOUND lpds=NULL;
static LPDIRECTINPUTDEVICE lpdiKeyboard=NULL,lpdiMouse=NULL;
// Initilize the DirectInput main COM interface
static void* DX_InitInput( void )
{
	if( FAILED(DirectInputCreate( hInstance , DIRECTINPUT_VERSION , &lpdi , NULL )) )
	{
		MessageBox( NULL , "Unable to create DirectInput interface" , "DX_comCreateInteface fault" , MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return NULL;
	}

	// create keyboard device
	if( FAILED(lpdi->CreateDevice( GUID_SysKeyboard , &lpdiKeyboard , NULL )) )
	{
		MessageBox( NULL , "unable to create LPDIRECTINPUTDEVICE GUID_SysKeyboard" , "DX_InitInterfaces fault" , MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return lpdi;
	}

	// create mouse device
	if( FAILED( lpdi->CreateDevice( GUID_SysMouse , &lpdiMouse , NULL )) )
	{
		MessageBox( NULL , "Unable to create LPDIRECTINPUTDEVICE GUID_SysMouse" , "DX_InitInterfaces fault" , MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return lpdi;
	}

	// set cooperation levels for initilized devices.
	lpdiKeyboard->SetCooperativeLevel( wndStruct.hWnd , DISCL_BACKGROUND | DISCL_NONEXCLUSIVE );
	   lpdiMouse->SetCooperativeLevel( wndStruct.hWnd , DISCL_BACKGROUND | DISCL_NONEXCLUSIVE );

    // set device generic data formats
    lpdiKeyboard->SetDataFormat( &c_dfDIKeyboard );
	   lpdiMouse->SetDataFormat( &c_dfDIMouse );

    // now acquire the devices from the initalized DirectInput interface
	if( FAILED( lpdiKeyboard->Acquire() ) ) 
	{
		MessageBox( NULL , "Unable to accuire GUID_SysKeyboard device" , "DX_InitInput fault" , MB_OK | MB_ICONEXCLAMATION );
		PostQuitMessage(0);
		return NULL;
	}

	if( FAILED( lpdiMouse->Acquire() ) )
	{
		MessageBox( NULL , "Unable to acquire GUID_SysMouse device" , "DX_InitInput fault" , MB_ICONEXCLAMATION | MB_OK );
		PostQuitMessage(0);
		return NULL;
	}

	return lpdi; 
}

// initilize all the DX com intefaces to be used by the engine.
void DX_InitInterfaces( void )
{
	DX_InitInput();
}

void DX_GetDeviceStates( void )
{
	if(FAILED(lpdiKeyboard->GetDeviceState(sizeof(k_byte) , di_KeyboardBuffer ) ) )
	{
	//	MessageBox(NULL , "Unable to poll GUID_SysKeyboard" , "DX_GetDeviceStates fault ; non-terminal" , MB_OK | MB_ICONINFORMATION );
	}

	if( FAILED(lpdiMouse->GetDeviceState(sizeof(DIMOUSESTATE) , &di_MouseState) ) )
	{
		MessageBox( NULL , "Unable to poll GUID_SysKeyboard" , "DX_GetDeviceStates fault ; non-terminal" , MB_OK | MB_ICONINFORMATION );
	}
}