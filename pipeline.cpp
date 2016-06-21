/***********************************************
 * $author: javery
 * $date  : 21 Nov 01
 * $descp : Pipeline routines.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Pipeline.h
 * $ver   : 0.0.0
 ***********************************************/

#include "pipeline.h"

void R_AllocQuere( pPipeline_Quere_t pQuere )
{
	pQuere->Elements = new k_word[ pQuere->QuereDepth ];
}

void R_AddElement( pPipeline_Quere_t pQuere , k_word element )
{
	pQuere->Elements[ pQuere->ActiveElements ] = element;
	pQuere->ActiveElements++;
}

void R_DeleteElement( pPipeline_Quere_t pQuere )
{
	pQuere->Elements[ pQuere->CurrentElement ] = R_PLN_NULL;
	pQuere->CurrentElement--;	
}

void R_ProcessElement( pPipeline_Quere_t pQuere )
{

}

void R_AddToScene( Model_t mdl )
{

}
