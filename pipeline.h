/***********************************************
 * $author: javery
 * $date  : 21 Nov 01
 * $descp : Pipeline routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Pipeline.h
 * $ver   : 0.0.0
 ***********************************************/

#ifndef __R_PIPELINE_H__
#define __R_PIPELINE_H__

#include "model.h"

typedef struct
{
	k_word QuereDepth , CurrentElement , ActiveElements;
	k_word* Elements;
}Pipeline_Quere_t , * pPipeline_Quere_t;

typedef enum
{
  R_PLN_NULL,      
  R_PLN_OVERFLOW,  
  R_PLN_UNDERFLOW, 
  R_PLN_SP_MODEL,  
  R_PLN_SP_WORLD,  
  R_PLN_SP_VIEW,   
  R_PLN_SP_SCREEN, 
  R_PLN_EXE_TRANS, 
  R_PLN_EXE_PROJECT,
  R_PLN_EXE_CLIP   
}PipeLine_State;

void R_Pl_AllocQuere( pPipeline_Quere_t );
void R_Pl_AddElement( pPipeline_Quere_t , PipeLine_State );
void R_Pl_DeleteElement( pPipeline_Quere_t  );
void R_Pl_ProcessElement( pPipeline_Quere_t );

void R_Pl_AddToScene( Model_t );
void R_Pl_AddToScene( Model_t* );

#endif 

