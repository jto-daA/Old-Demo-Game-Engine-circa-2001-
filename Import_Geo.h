/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Routines to import data from AutoDesk 3D-
 *          Studio Max ( thanks to By Jeff Lewis (werewolf@worldgate.com) for the file spec )
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Import_geo.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __UTIL_3DS_IMPORT_H__
#define __UTIL_3DS_IMPORT_H__

#include "util_common_h.h"
#include "vector.h"
#include "polygon.h"
#include "model.h"

#include <stdio.h>

#define IG_3DS_VERSION_OFFSET                               0x001C

#define IG_3DS_ID_M3DMAGIC                                  0x4D4D
  #define IG_3DS_EDIT                                       0x3D3D     
    #define IG_3DS_ID_EDIT_MATERIAL                         0xAFFF
    #define IG_3DS_ID_EDIT_CONFIG_01                        0x0100
    #define IG_3DS_ID_EDIT_CONFIG_02                        0x3E3D
    #define IG_3DS_ID_EDIT_VIEW_P01                         0x7012
    #define IG_3DS_ID_EDIT_VIEW_P02                         0x7011
    #define IG_3DS_ID_EDIT_VIEW_P03                         0x7020
    #define IG_3DS_ID_EDIT_VIEW_01                          0x7001
    #define IG_3DS_ID_EDIT_BACKGROUND                       0x1200
    #define IG_3DS_ID_EDIT_AMBIENT                          0x2100
    #define IG_3DS_ID_OBJECT                                0x4000
     #define IG_3DS_ID_OBJECT_MESH                          0x4100
      #define IG_3DS_ID_VERTEX_ARRAY                        0x4110
      #define IG_3DS_ID_VERTEX_FLAG_ARRAY                   0x4111
      #define IG_3DS_ID_FACE_INDICIES                       0x4120
      #define IG_3DS_ID_FACE_MATERIAL                       0x4130 
      #define IG_3DS_ID_MAPPING_COORDS                      0x4140

/* New keyframe macros added 31 NOV 02 */
  #define IG_3DS_KEYFRAME                                   0xB000
    #define IG_3DS_KEYFRAME_GBL_HEADER                      0xB00A
    #define IG_3DS_KEYFRAME_GBL_ACT_SEG                     0xB008
    #define IG_3DS_KEYFRAME_GBL_CURR_FRAME                  0xB009

      #define IG_3DS_KEYFRAME_NODE_OBJ                      0xB002     

         #define IG_3DS_KEYFRAME_NODE_OBJ_NODE_ID           0xB030
         #define IG_3DS_KEYFRAME_NODE_OBJ_NODE_HDR          0xB010
         #define IG_3DS_KEYFRAME_NODE_OBJ_PIVOT             0xB013                    
         #define IG_3DS_KEYFRAME_NODE_OBJ_INSTANCE_NAME     0xB011
         #define IG_3DS_KEYFRAME_NODE_OBJ_BOUNDBOX          0xB014
         #define IG_3DS_KEYFRAME_NODE_OBJ_POS_TRACK         0xB020
         #define IG_3DS_KEYFRAME_NODE_OBJ_ROT_TRACK         0xB021
         #define IG_3DS_KEYFRAME_NODE_OBJ_SCL_TRACK         0xB022
         #define IG_3DS_KEYFRAME_NODE_OBJ_MORPH_TRACK       0xB026
         #define IG_3DS_KEYFRAME_NODE_OBJ_HIDE_TRACK        // hmmmmmm....
         #define IG_3DS_KEYFRAME_NODE_OBJ_MORPH_SMOOTH      0xB015

/* MAKE THE NECESSARY ROUTINES STATIX!!!! */
static k_word IG_3DS_ReturnVersionNumber( FILE* );
long IG_3DS_FindChunkID( k_word , FILE* );
static long IG_3DS_SkipChunk( k_word , FILE* );
static long IG_3DS_SkipToChunk( k_word , FILE* );
static void IG_3DS_LoadTexture( Model_t* , FILE* );
static void IG_3DS_LoadChildren( Model_t* , FILE* ,FILE* );
static void IG_3DS_LoadObject( Model_t* , FILE* );
void IG_3DS_LoadObject( Model_t* , char* );

/* New routines for keyframing data 31 NOV 02 */
static void IG_3DS_LoadGlobalKeyframeData( FILE* , p3DS_GlobalKeyframe_t );
static void IG_3DS_InitKeyframes( pKeyframeData_t );
static void IG_3DS_LoadKeyframeData( FILE* , pKeyframeData_t );

#endif /* __UTIL_3DS_IMPORT_H__ */

