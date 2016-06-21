/***********************************************
 * $author: javery
 * $date  : 25 Nov 03
 * $descp : Revamped,rethought approach to depricated import_geo.cpp.
 *          close to its 2 year pathetic anniversery
 * $path  : D:\Program Files\Microsoft Visual Studio\MyProjects\KaosEngineWorking\import_3ds.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __IMPORT3DS_H__
#define __IMPORT3DS_H__

#include "vector.h"
#include "polygon.h"
#include "model.h"

#include "util_end_h.h"
#include "import_geo.h"

#include <stdio.h>

// helper routines. 

// main routine.
static void Import3DSObject( pModel_t , FILE* );

// user routines
int Import3DSObject( pModel_t , char* );

#endif 
