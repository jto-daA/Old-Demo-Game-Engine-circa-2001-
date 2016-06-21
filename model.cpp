/***********************************************
 * $author: javery
 * $date  : 10 Nov 01
 * $descp : Data structure for engine models ( scene objects )
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\Model.cpp
 * $ver   : 0.0.0
 ***********************************************/

#include "model.h"
#include "texture.h"

#include <windows.h>
#include <gl/gl.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

void ENT_M_LambertRenderer( pModel_t pMod )
{
	Vect3_t normal;

	glShadeModel( GL_FLAT );

	for(int index = 0;index < pMod->polyCount ; index++)
    {
		float x,y,z;

	      glBegin( GL_TRIANGLES );

		  glNormal3f( pMod->polygons[index].Normal.xComponent ,
			          pMod->polygons[index].Normal.yComponent ,
					  pMod->polygons[index].Normal.zComponent );

		  x = pMod->polygons[index].pVerticies[0]->xComponent,
          y = pMod->polygons[index].pVerticies[0]->yComponent,
		  z = pMod->polygons[index].pVerticies[0]->zComponent;
		  
		  glVertex3f( x , y , z );

		  x = pMod->polygons[index].pVerticies[1]->xComponent,
          y = pMod->polygons[index].pVerticies[1]->yComponent,
		  z = pMod->polygons[index].pVerticies[1]->zComponent;

		  glVertex3f( x , y , z );

		  x = pMod->polygons[index].pVerticies[2]->xComponent,
          y = pMod->polygons[index].pVerticies[2]->yComponent,
		  z = pMod->polygons[index].pVerticies[2]->zComponent;

		glVertex3f( x , y , z );

		glEnd();
	}

    if( pMod->hasChildren )
	{
		pModel_t nextChild = pMod->pChildren;
		
		while(nextChild != NULL)
		{
			ENT_M_LambertRenderer( nextChild );

			nextChild = nextChild->pChildren;
		}
	}	
}

void ENT_M_GouraudRenderer( pModel_t pMod )
{

}

void ENT_M_WireFrameRenderer( pModel_t pMod )
{
	Vect3_t vDefault;
	MTV_Init( vDefault , 0 , 0 , 1 );

	glShadeModel( GL_FLAT );

	for(int index = 0;index < pMod->polyCount ; index++)
    {
#ifdef K32_DEBUG_v_0		
		if( pMod->polygons[index].bspNode ) 
		{
			glShadeModel( GL_FLAT );
			glBegin( GL_TRIANGLES );
			glColor3d( 1 , 0.5f , 1 );
		}

		else
		{
			glBegin( GL_LINES );		    
		    glColor3d( 1 , 1 , 1 );
		}
#else
		glBegin( GL_LINES );
		glColor3d( 1 , 1 , 1 );
#endif
		glVertex3f(   pMod->polygons[index].pVerticies[0]->xComponent ,
			          pMod->polygons[index].pVerticies[0]->yComponent ,
					  pMod->polygons[index].pVerticies[0]->zComponent );

		  glVertex3f( pMod->polygons[index].pVerticies[1]->xComponent ,
			          pMod->polygons[index].pVerticies[1]->yComponent ,
					  pMod->polygons[index].pVerticies[1]->zComponent );

		  glVertex3f( pMod->polygons[index].pVerticies[1]->xComponent ,
			          pMod->polygons[index].pVerticies[1]->yComponent ,
					  pMod->polygons[index].pVerticies[1]->zComponent );

		  glVertex3f( pMod->polygons[index].pVerticies[2]->xComponent ,
			          pMod->polygons[index].pVerticies[2]->yComponent ,
					  pMod->polygons[index].pVerticies[2]->zComponent );

		  glVertex3f( pMod->polygons[index].pVerticies[2]->xComponent ,
			          pMod->polygons[index].pVerticies[2]->yComponent ,
					  pMod->polygons[index].pVerticies[2]->zComponent );

		  glVertex3f( pMod->polygons[index].pVerticies[0]->xComponent ,
			          pMod->polygons[index].pVerticies[0]->yComponent ,
					  pMod->polygons[index].pVerticies[0]->zComponent );

		glEnd();
	}

	if( pMod->hasChildren )
	{
		pModel_t nextChild = pMod->pChildren;
		
		while( nextChild )
		{
			ENT_M_WireFrameRenderer( nextChild );

			nextChild = nextChild->pChildren;
		}
	}	
}
void ENT_M_PWTextureRenderer( pModel_t pMod )
{


}

void ENT_M_SkTextureRenderer( pModel_t pMod )
{
	int index=0;
	
	R_Tx_UseTexture( pMod->textureRef );

	glEnable( GL_TEXTURE_2D );

	for(index = 0; index < pMod->polyCount; index++)
	{
		glBegin( GL_TRIANGLES );
		glTexCoord2f( pMod->polygons[ index ].pVerticies[0]->uComponent,
		              pMod->polygons[ index ].pVerticies[0]->vComponent );
	    glVertex3d(   pMod->polygons[ index ].pVerticies[0]->xComponent , 
		              pMod->polygons[ index ].pVerticies[0]->yComponent ,
			    	  pMod->polygons[ index ].pVerticies[0]->zComponent );  

		glTexCoord2f( pMod->polygons[ index ].pVerticies[1]->uComponent,
		              pMod->polygons[ index ].pVerticies[1]->vComponent );
	    glVertex3d(   pMod->polygons[ index ].pVerticies[1]->xComponent , 
		              pMod->polygons[ index ].pVerticies[1]->yComponent ,
   				      pMod->polygons[ index ].pVerticies[1]->zComponent );  

		glTexCoord2f( pMod->polygons[ index ].pVerticies[2]->uComponent,
		              pMod->polygons[ index ].pVerticies[2]->vComponent );
		glVertex3d(   pMod->polygons[ index ].pVerticies[2]->xComponent , 
			          pMod->polygons[ index ].pVerticies[2]->yComponent ,
					  pMod->polygons[ index ].pVerticies[2]->zComponent );  
		glEnd();
	}

	if( pMod->hasChildren )
	{ 
	    pModel_t nextChild = pMod->pChildren;
			
		while(nextChild != NULL)
		{
			ENT_M_SkTextureRenderer( nextChild );
			nextChild = nextChild->pChildren;
		}
	}	
}

pModel_t ENT_M_AddChild( pModel_t pParent )
{
	Model_t* search = pParent;

	if( search->pChildren != NULL )
	{
		while( search->pChildren != NULL )
		{
			search = search->pChildren;
		}
	}

	search->pChildren = new Model_t;
	search->pChildren->pChildren = NULL;

	return search->pChildren;
}
 
void ENT_M_InitStandAlone( pModel_t pModel )
{
	memset( pModel , 0 , sizeof(Model_t) );
	pModel->hasChildren = k_false;
	pModel->Parent = NULL;
	pModel->pChildren = NULL;
}

void ENT_M_InitHierarchy( pModel_t pModel )
{
	memset( pModel , 0 , sizeof(Model_t) );
	pModel->hasChildren = k_true;
	pModel->Parent = pModel;
	pModel->pChildren = NULL;
}

void MTP_Strip( pModel_t obj , pPolySet_t pSet )
{
	pModel_t currObj=obj;
	int totalCount=0,index=0;
	
	do
	{
		totalCount += currObj->polyCount;
		currObj = currObj->pChildren;
	}while( currObj != NULL );

	currObj = obj;

	pSet->pPolygons = new pPoly_t[ totalCount+1 ];
	pSet->setSize = totalCount;

	do
	{
		for( int i=0;i < currObj->polyCount;index++,i++)
		pSet->pPolygons[ index ] = &currObj->polygons[i];

		currObj = currObj->pChildren;

	}while( currObj != NULL );

	pSet->pPolygons[index + 1] = NULL;
}


	
	




