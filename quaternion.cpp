/***********************************************
 * $author: javery
 * $date  : 08 Feb 03
 * $descp : fun with quaternions. 
 * $path  : C:\Program Files\Microsoft Visual Studio\MyProjects\KaosDemoEngine\quaternion.h
 * $ver   : 0.0.0
 ***********************************************/


#include "quaternion.h"

void MTQ_Init( Quaternion_t* pq , float s , float i , float j , float k )
{
	pq->s = s;
	pq->v.i = i;
	pq->v.j = j;
	pq->v.k = k;
}

void MTQ_Init( Quaternion_t* pq , float s , Vect3_t v3 )
{
	pq->s = s;
	pq->v.i = v3.xComponent;
	pq->v.j = v3.yComponent;
	pq->v.k = v3.zComponent;
}

Vect3_t MTQ_Convert( Quaternion_t* pq )
{ 
	Vect3_t rv; 

	MTV_Init( rv , pq->v.i , pq->v.j , pq->v.k );

	return rv; 
}


Quaternion_t MTQ_Conjugate( Quaternion_t* pq )
{
	Q rQ;

	MTQ_Init( &rQ , pq->s , -pq->v.i , -pq->v.j , -pq->v.k );

	return rQ;
}

Quaternion_t MTQ_Add( Quaternion_t* pq1 , Quaternion_t* pq2 )
{
	Q rQ;

	MTQ_Init( &rQ , 
		      pq1->s + pq2->s , 
			  pq1->v.i + pq2->v.i , 
			  pq1->v.j + pq2->v.j , 
			  pq1->v.k + pq2->v.k 
			 );

	return rQ;
}

Quaternion_t MTQ_Multiply( Quaternion_t* pq1 , Quaternion_t* pq2 )
{
/*	Q rQ;
	Vect3_t work1 = MTQ_Convert( pq1 ) , 
		    work2 = MTQ_Convert( pq2 ) , 
			term1 = MTV_Scale( work1 , pq2->s ) ,
			term2 = MTV_Scale( work2 , pq1->s ) ,
			term3 = MTV_CrossProd( work1 , work2 ),	// making the quaternion noncommutitve. 		
	        sum;
	MTV_Init( sum , 
		      term1.xComponent + term2.xComponent + term3.xComponent , 
			  term1.yComponent + term2.yComponent + term3.yComponent , 
			  term1.zComponent + term2.zComponent + term3.zComponent 
			);

	MTQ_Init( &rQ , 
		       (pq1->s*pq2->s)-(MTV_DotProd( work1 , work2 )) , 
			   sum			    
     		);

	return rQ;*/

	/*
	  w = w1w2 - x1x2 - y1y2 - z1z2
      
	  x = w1x2 + x1w2 + y1z2 - z1y2
    
	  y = w1y2 + y1w2 + z1x2 - x1z2
     
	  z = w1z2 + z1w2 + x1y2 - y1x2 
*/
	float s,i,j,k;
	Q product;

    s = ( pq1->s * pq2->s ) - ( pq1->v.i * pq2->v.i ) - ( pq1->v.j * pq2->v.j ) - ( pq1->v.k * pq2->v.k );
	i = ( pq1->s * pq2->v.i ) + ( pq1->v.i * pq2->s ) + ( pq1->v.j * pq2->v.k ) - ( pq1->v.k * pq2->v.j ); 
	j = ( pq1->s * pq2->v.j ) + ( pq1->v.j * pq2->s ) + ( pq1->v.k * pq2->v.i ) - ( pq1->v.i * pq2->v.k ); 
	k = ( pq1->s * pq2->v.k ) + ( pq1->v.k * pq2->s ) + ( pq1->v.i * pq2->v.j ) - ( pq1->v.j * pq2->v.i ); 


    MTQ_Init( &product , s , i , j , k );
	
	return product;  
}

float MTQ_Lenght( Quaternion_t* pq )
{
	Q derQ = MTQ_Conjugate( pq ),
	  prod = MTQ_Multiply( pq , &derQ ); 
	return prod.s;
}

void MTQ_Clear( Quaternion_t* pq )
{
	pq->s = 0; 
	pq->v.i = pq->v.j = pq->v.k = 0;
}

void MTQ_Negate( Quaternion_t* pq )
{
	pq->s = -pq->s;
	pq->v.i = -pq->v.i;
	pq->v.j = -pq->v.j;
	pq->v.k = -pq->v.k;
}

void MTQ_Normalize( Quaternion_t* pq )
{
/*	Vect3_t work = MTQ_Convert( pq ); 
	MTV_Normalize( work ); 
	pq->v.i = work.xComponent; 
	pq->v.j = work.yComponent;
	pq->v.k = work.zComponent;*/

	float lenght = MTQ_Lenght( pq ); 

	pq->s /= lenght; 
	pq->v.i /= lenght; 
	pq->v.j /= lenght; 
	pq->v.k /= lenght; 

}
	

	

