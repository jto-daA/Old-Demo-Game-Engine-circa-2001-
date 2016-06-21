/***********************************************
 * $author: javery
 * $date  : 9 Mar 02
 * $descp : BSP renderer.
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\bsp_ren.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "bsp_comp.h"
#include "bsp_ren.h"
#include "camera.h"
#include "polygon.h"

#include <windows.h>
#include <gl/gl.h>

/* 
**************************************************
* R_BSP_RenderNode
* Renders the specified bsp node, and all pertinent
* data (light/texturemaps). 
**************************************************
*/
void R_BSP_RenderNode( pbspNode_t pNode , pCamera_t pCam )
{
	pPoly_t ppoly = pNode->pPoly;
	pVect3_t pnormal = &ppoly->Normal;

	if( pNode == NULL )
	{
		return;
	}
	
	glPushMatrix();

	if( pNode->type == NT_TREE )
	{
		if( 1 )
		{			
			if( !PLY_FLG_TYPE(ppoly->PolyFlag) )
			{
				glBegin( GL_LINES );
 
				glNormal3f( pnormal->xComponent , pnormal->yComponent , pnormal->zComponent ); 	  

				glVertex3f( ppoly->pVerticies[ 0 ]->xComponent , ppoly->pVerticies[ 0 ]->yComponent , ppoly->pVerticies[ 0 ]->zComponent );
		     	glVertex3f( ppoly->pVerticies[ 1 ]->xComponent , ppoly->pVerticies[ 1 ]->yComponent , ppoly->pVerticies[ 1 ]->zComponent );

				glVertex3f( ppoly->pVerticies[ 1 ]->xComponent , ppoly->pVerticies[ 1 ]->yComponent , ppoly->pVerticies[ 1 ]->zComponent );
		     	glVertex3f( ppoly->pVerticies[ 2 ]->xComponent , ppoly->pVerticies[ 2 ]->yComponent , ppoly->pVerticies[ 2 ]->zComponent );
              
				glVertex3f( ppoly->pVerticies[ 2 ]->xComponent , ppoly->pVerticies[ 2 ]->yComponent , ppoly->pVerticies[ 2 ]->zComponent );
             	glVertex3f( ppoly->pVerticies[ 0 ]->xComponent , ppoly->pVerticies[ 0 ]->yComponent , ppoly->pVerticies[ 0 ]->zComponent );  
			
				glEnd();
			}

			else
			{
				/*glBegin( GL_QUADS );

				glNormal3f( pnormal->xComponent , pnormal->yComponent , pnormal->zComponent );

				glVertex3f( ppoly->pVerticies[0]->xComponent,ppoly->pVerticies[0]->yComponent , ppoly->pVerticies[0]->zComponent );
				glVertex3f( ppoly->pVerticies[1]->xComponent,ppoly->pVerticies[1]->yComponent , ppoly->pVerticies[1]->zComponent );
				
				glVertex3f( ppoly->pVerticies[1]->xComponent,ppoly->pVerticies[1]->yComponent , ppoly->pVerticies[1]->zComponent );
				glVertex3f( ppoly->pVerticies[2]->xComponent,ppoly->pVerticies[2]->yComponent , ppoly->pVerticies[2]->zComponent );

				glVertex3f( ppoly->pVerticies[2]->xComponent,ppoly->pVerticies[2]->yComponent , ppoly->pVerticies[2]->zComponent );
				glVertex3f( ppoly->pVerticies[3]->xComponent,ppoly->pVerticies[3]->yComponent , ppoly->pVerticies[3]->zComponent );

				glVertex3f( ppoly->pVerticies[3]->xComponent,ppoly->pVerticies[3]->yComponent , ppoly->pVerticies[3]->zComponent );
				glVertex3f( ppoly->pVerticies[0]->xComponent,ppoly->pVerticies[0]->yComponent , ppoly->pVerticies[0]->zComponent );

				glEnd();*/
			}
		}
	}
		
	else if( pNode->type == NT_LEAF )
	{
	   	for(int index = 0;index < pNode->Polys.setSize-1;index++)
		{
			if( 1 )
			{  
				// add aliases to this code block.
				if( !PLY_FLG_TYPE(pNode->Polys.pPolygons[ index ]->PolyFlag) )
				{
					glBegin( GL_LINES );

					           
					glNormal3f( pNode->Polys.pPolygons[ index ]->Normal.xComponent ,
					            pNode->Polys.pPolygons[ index ]->Normal.yComponent ,
							    pNode->Polys.pPolygons[ index ]->Normal.zComponent );
				
				   	glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->zComponent );

	                glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->yComponent ,
					            pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->zComponent );

	               	glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->zComponent );
    	           
					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->zComponent );
    	           
					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->zComponent );
               
					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->zComponent );
   	          
					glEnd();
				}

			/*	else// if( pNode->Polys.pPolygons[ index ]->PolyFlag==PT_QUADRANGULAR )
				{
					glBegin( GL_LINES );
	               
					glNormal3f( pNode->Polys.pPolygons[ index ]->Normal.xComponent ,
				 	            pNode->Polys.pPolygons[ index ]->Normal.yComponent ,
							    pNode->Polys.pPolygons[ index ]->Normal.zComponent );
				
				   	glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->zComponent );

	                glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->yComponent ,
					            pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->zComponent );

	               	glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->zComponent );
    	           
					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->zComponent );
    	           
					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->zComponent );
               
					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 3 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 3 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 3 ]->zComponent );

					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 3 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 3 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 3 ]->zComponent );

					glVertex3f( pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->xComponent , 
				                pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->yComponent ,
						        pNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->zComponent );

					glEnd();
				}*/
			}
		}
	}

	glPopMatrix();	
}

/*
**************************************************
* R_BSP_RecurseRootNode
* In-onder walk/rendering of compiled bsp tree. 
**************************************************
*/
void R_BSP_RecurseRootNode( pbspNode_t pRootNode , pCamera_t pCam )
{
	static pbspNode_t nodeLine = pRootNode;
	float eval=0.0f;

	if( pRootNode == NULL )
	{
		return;
	}

/*	float fEval = MTPl_Evaluate( &pRootNode->SplitPlane , &pCam->Direction );

	if( fEval < 0 )
    // case 1 : viewport behiend partioning plane.
	{
		R_BSP_RecurseRootNode( pRootNode->prChild , pCam );
		R_BSP_RenderNode( pRootNode , pCam );
		R_BSP_RecurseRootNode( pRootNode->plChild , pCam );
	}

	if( fEval > 0 )
	// case 2 : viewport in front of partioning plane.
	{
		R_BSP_RecurseRootNode( pRootNode->plChild , pCam );
		R_BSP_RenderNode( pRootNode , pCam );
	    R_BSP_RecurseRootNode( pRootNode->prChild , pCam );
	}

	else
	// ambigious case ( viewport consistent with partioning plane ).
	{
//		R_BSP_RecurseRootNode( pRootNode->plChild , pCam );
//		R_BSP_RecurseRootNode( pRootNode->prChild , pCam );
	}	*/

	// tree partioning plane.
	if( pRootNode->type == NT_TREE )
	{
		// NOTE: this could become buggy. Take the position into account.
		eval = MTPl_Evaluate( &pRootNode->SplitPlane , &pCam->Position );

		if( eval < 0 )
		{
			R_BSP_RecurseRootNode( pRootNode->plChild , pCam );
			R_BSP_RecurseRootNode( pRootNode->prChild , pCam );
		}

		else
		{
			R_BSP_RecurseRootNode( pRootNode->prChild , pCam );
			R_BSP_RecurseRootNode( pRootNode->plChild , pCam );
		}
	}

	// tree leave ( containing pushed polygons set )
	else
	{
		for(int index = 0;index < pRootNode->Polys.setSize;index++)
		{
			glBegin( GL_LINES );
            
			glNormal3f( pRootNode->Polys.pPolygons[ index ]->Normal.xComponent ,
				 	    pRootNode->Polys.pPolygons[ index ]->Normal.yComponent ,
						pRootNode->Polys.pPolygons[ index ]->Normal.zComponent );
				
			glVertex3f( pRootNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->xComponent , 
				        pRootNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->yComponent ,
					    pRootNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->zComponent );

	        glVertex3f( pRootNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->xComponent , 
				        pRootNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->yComponent ,
					    pRootNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->zComponent );

	        glVertex3f( pRootNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->xComponent , 
				        pRootNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->yComponent ,
					    pRootNode->Polys.pPolygons[ index ]->pVerticies[ 1 ]->zComponent );
    	           
			glVertex3f( pRootNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->xComponent , 
				        pRootNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->yComponent ,
					    pRootNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->zComponent );
    	           
			glVertex3f( pRootNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->xComponent , 
				        pRootNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->yComponent ,
					    pRootNode->Polys.pPolygons[ index ]->pVerticies[ 2 ]->zComponent );
               
			glVertex3f( pRootNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->xComponent , 
				        pRootNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->yComponent ,
					    pRootNode->Polys.pPolygons[ index ]->pVerticies[ 0 ]->zComponent );

			glEnd();
		}

	}
}