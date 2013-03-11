#include "API_Gene_instance.h"
#include<stdio.h>

void Gene_instance_genere_matrice(int nbcase, int nbcl, int nivdif, int graine, int **M){
  int i,j,k,m,c,di,si,prof,larg;

  int diam= (nivdif/100.0)*nbcase;
  if (diam==0) diam=1;
  srand(graine);

  for (j=0;j<nbcase;j++)
    for (i=0;i<nbcase;i++)
      M[i][j]=-1;
 
  for (j=0;j<nbcase;j++)
    for (i=0;i<nbcase;i++){

      if (M[i][j]==-1){

	c=rand()%(nbcl);

	prof=1+rand()%(diam);
	larg=1+rand()%(diam);

	k=0;
	while ((k<prof)&&(j+k<nbcase)){

	  M[i][j]=c;
	  
	  di=(rand()%larg)/4.0;
	  si=1-2*rand()%2;
	  m=0;
	  while (m<larg){

	    if ((i+si*di+m>=0)&&(i+si*di+m<nbcase)&&(M[i+si*di+m][j+k]==-1))
	      M[i+si*di+m][j+k]=c;
	    m++;
	  }

	  k++;
	}

      }
    }
 
}
