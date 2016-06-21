# Microsoft Developer Studio Project File - Name="KaosDemoEngine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KaosDemoEngine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KaosDemoEngine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KaosDemoEngine.mak" CFG="KaosDemoEngine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KaosDemoEngine - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KaosDemoEngine - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KaosDemoEngine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "KaosDemoEngine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib OpenGL32.lib glaux.lib glu32.lib dinput.lib dxguid.lib /nologo /subsystem:windows /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "KaosDemoEngine - Win32 Release"
# Name "KaosDemoEngine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\alg_surf.cpp
# End Source File
# Begin Source File

SOURCE=.\import_3ds.cpp
# End Source File
# Begin Source File

SOURCE=.\Import_Geo.cpp
# End Source File
# Begin Source File

SOURCE=.\k_globals.cpp
# End Source File
# Begin Source File

SOURCE=.\md2Loader.cpp
# End Source File
# Begin Source File

SOURCE=.\text.cpp
# End Source File
# Begin Source File

SOURCE=.\util_end.cpp
# End Source File
# End Group
# Begin Group "Math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\plane.cpp
# End Source File
# Begin Source File

SOURCE=.\Polygon.cpp
# End Source File
# Begin Source File

SOURCE=.\quaternion.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector.cpp
# End Source File
# End Group
# Begin Group "Entities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\model.cpp
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Group "input"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DXWrapper.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\OpenGL.cpp
# End Source File
# Begin Source File

SOURCE=.\Win32.cpp
# End Source File
# End Group
# Begin Group "Renderer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bsp_comp.cpp
# End Source File
# Begin Source File

SOURCE=.\bsp_ren.cpp
# End Source File
# Begin Source File

SOURCE=.\light.cpp
# End Source File
# Begin Source File

SOURCE=.\texture.cpp
# End Source File
# Begin Source File

SOURCE=.\z_buffer.cpp
# End Source File
# End Group
# Begin Group "Bitmap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\pcx.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\EndianDemo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Utilities_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\alg_surf.h
# End Source File
# Begin Source File

SOURCE=.\import_3ds.h
# End Source File
# Begin Source File

SOURCE=.\Import_Geo.h
# End Source File
# Begin Source File

SOURCE=.\md2Loader.h
# End Source File
# Begin Source File

SOURCE=.\text.h
# End Source File
# Begin Source File

SOURCE=.\util_common_h.h
# End Source File
# Begin Source File

SOURCE=.\util_end_h.h
# End Source File
# End Group
# Begin Group "Math_h"

# PROP Default_Filter ".h , .hpp"
# Begin Source File

SOURCE=.\Matrix.h
# End Source File
# Begin Source File

SOURCE=.\mth_common.h
# End Source File
# Begin Source File

SOURCE=.\plane.h
# End Source File
# Begin Source File

SOURCE=.\Polygon.h
# End Source File
# Begin Source File

SOURCE=.\quaternion.h
# End Source File
# Begin Source File

SOURCE=.\vector.h
# End Source File
# End Group
# Begin Group "Entities_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\camera.h
# End Source File
# Begin Source File

SOURCE=.\Model.h
# End Source File
# End Group
# Begin Group "System_h"

# PROP Default_Filter ""
# Begin Group "input_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DxWrapper.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\OpenGL.h
# End Source File
# Begin Source File

SOURCE=.\Win32.h
# End Source File
# End Group
# Begin Group "Renderer_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bsp_comp.h
# End Source File
# Begin Source File

SOURCE=.\bsp_ren.h
# End Source File
# Begin Source File

SOURCE=.\light.h
# End Source File
# Begin Source File

SOURCE=.\pipeline.h
# End Source File
# Begin Source File

SOURCE=.\texture.h
# End Source File
# Begin Source File

SOURCE=.\z_buffer.h
# End Source File
# End Group
# Begin Group "Bitmap_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\pcx.h
# End Source File
# Begin Source File

SOURCE=.\perlin.h
# End Source File
# Begin Source File

SOURCE=.\text_gen.h
# End Source File
# End Group
# End Group
# Begin Group "test meshes"

# PROP Default_Filter "3ds"
# Begin Group "3DS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\3dm-keybord.3ds"
# End Source File
# Begin Source File

SOURCE=".\3dm-q2hyperb.3ds"
# End Source File
# Begin Source File

SOURCE=".\3dm-q2rail.3ds"
# End Source File
# Begin Source File

SOURCE=".\3dm-q2shotgun2.3ds"
# End Source File
# Begin Source File

SOURCE=".\3dm-towersys.3ds"
# End Source File
# Begin Source File

SOURCE=.\ast.3DS
# End Source File
# Begin Source File

SOURCE=.\character.3ds
# End Source File
# Begin Source File

SOURCE=.\guts.3ds
# End Source File
# Begin Source File

SOURCE=.\tpot.3ds
# End Source File
# Begin Source File

SOURCE=.\work.3DS
# End Source File
# Begin Source File

SOURCE=.\work2.3DS
# End Source File
# End Group
# Begin Group "MD2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\knight.md2
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Test textures"

# PROP Default_Filter ""
# Begin Group "3DS_textures"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hyperb.bmp
# End Source File
# Begin Source File

SOURCE=.\rail.bmp
# End Source File
# Begin Source File

SOURCE=.\shotgun2.bmp
# End Source File
# End Group
# End Group
# Begin Group "plan"

# PROP Default_Filter "txt"
# Begin Source File

SOURCE=.\06_mar_2.txt
# End Source File
# End Group
# Begin Group "hex dumps"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\good_hex
# End Source File
# Begin Source File

SOURCE=.\work_ed
# End Source File
# End Group
# End Target
# End Project
