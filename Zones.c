#ifndef ZONESC
#define ZONESC

#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"
#include "Zones.h"

//Renvoie une nouvelle Zone et test le succes des allocations
void init_Zones (int **M, Zones *newZone) {
  int i, j;

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  /*
  newZone = NULL;
  newZone = (Zones *) malloc(sizeof(Zones));
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  */

  newZone->Lzsg = NULL; //Initialisation a NULL pour test du succes du malloc
  newZone->B = NULL;
  //// AAARGH SEGFAULT C'EST NORMAL
  newZone->App =  malloc(sizeof(int *) * newZone->nbcase);
  if(newZone->App == NULL)
    {
      fprintf(stderr, "Allocation de App failed!\n");
      exit(EXIT_FAILURE);
    }
  for(i=0; i < newZone->nbcase; i++)
    {
      newZone->App[i] =  malloc(sizeof(int) * newZone->nbcase); 
      for(j=0; j < newZone->nbcase; j++)
	{
	  newZone->App[i][j] = -2;
	}

    }

  int a, b;
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  for(a=0; a<newZone->nbcase; a++)
    {
      newZone->App[0][a] = -2;
    }
  for(a=0; a<newZone->nbcase; a++){
    for(b=0; b<newZone->nbcase; b++){
      printf("%d\t", newZone->App[a][b]);
    }
    printf("\n");
  }

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

  newZone->B = malloc(sizeof(Liste_case *) * newZone->nbcl);
  if(newZone->B == NULL)
    {
      fprintf(stderr, "Allocation de B failed!\n");
      exit(EXIT_FAILURE);
    }
  for(i=0; i < newZone->nbcl; i++)
    {
      newZone->B[i] = NULL;
    }


  newZone->Lzsg = (Liste_case *) malloc(sizeof(Liste_case));


  if( (newZone->Lzsg == NULL) || (newZone->B == NULL))
    {
      exit(EXIT_FAILURE);
    }

  //Valeurs de demarrage
  ajoute_Zsg(newZone, 0, 0);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  ajoute_Bordure(newZone, 0, 1, M[0][1]);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  ajoute_Bordure(newZone, 1, 0, M[1][0]);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  ajoute_Bordure(newZone, 1, 1, M[1][1]);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

  //return newZone;

}

//Ajoute une element a la liste des Zsg et modifide App
void ajoute_Zsg(Zones *z, int i, int j)
{
  if( (i > z->nbcase) || (j > z->nbcase))
    {
      exit(EXIT_FAILURE);
    }

  if(z->App[i][j] != -1)
    {
      //Remplace la liste par une nouvelle liste contenant la case supplemantaire
      z->Lzsg =  ajouteListe(z->Lzsg, i, j); 

      //Remplace la reference a la liste dans le tableau App
      z->App[i][j] = -1;
    }
}

//Ajoute un element a la bordure et change sa reference dans App avec cl
void ajoute_Bordure(Zones *z, int i, int j, int clCase)
{
  if( (i > z->nbcase) || (j > z->nbcase))
    {
      exit(EXIT_FAILURE);
    }
  //Remplace la liste par une nouvelle liste contenant la case supplemantaire
  z->B[clCase] =  ajouteListe(z->B[clCase], i, j); 

  //Remplace la reference a la liste dans le tableau App
  if(clCase<100){
    z->App[i][j] = clCase;
  }
  fprintf(stderr, "%s %d\t App[%d][%d] = %d \t\t Verif: %d\n", __FILE__, __LINE__, i, j, clCase, z->App[i][j]);

}

//Renvoie vrai si la case appartient a la Bordure
int appartient_Bordure_coord(Zones *z, int i, int j)
{
  //Si la ref dans App correspond a une couleur, elle appartient a la bordure et est plus grande que 0
  return (z->App[i][j] > 0);
}

//Renvoie vrai si la case appartient a la Zsg
int appartient_Zsg(Zones *z, int i, int j)
{
  printf(" %s %d\tappartient_Zsg \tI:%d \tJ:%d \n", __FILE__, __LINE__, i, j);
  //Si la ref dans App est egale a -1, (i,j) est presente dans la Zsg 
  printf("App:\t%d\n", z->App[i][j]);
  return (z->App[i][j] == -1);
}

//Renvoie vrai si la couleur est presente dans la bordure
int appartient_Bordure(int ** M, Zones *z, int cl)
{
  Liste_case *l = NULL;
  l = z->B[cl];
  int i,j;

  while(1)
    {
      if(l == NULL)
	{
	  return 0;
	}
      i = l->i;
      j = l->j;


      if(M[i][j] == cl)
	{
	  return 1;
	}

      l = l->next;
    }
}

void colorieZone (int **M, Zones *Z, int cl, int *cpt)
{

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

  Liste_case *e = Z->Lzsg;
  int i, j;

  *cpt = 0; //init du compteur

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  while(e != NULL)
    {	
      i = e->i;
      j = e->j;


      fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
      if ((i < Z->nbcase) && (j < Z->nbcase))
	{
	  M[i][j] = cl;
	}
      fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
      e = e->next; 

      (*cpt)++;
    }

}
void aggranditZone(int ** M, Zones *z, int cl)
{
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  int i, j, nbcase = z->nbcase, **v;
  Pile p;  //p-> cases a visiter, v cases visitees. Si v[i][j] == 1, la case (i,j) ne dois pas etre empilee
  Element *e = NULL;
  Liste_case *l = z->B[cl];
  init_pile(&p);


  v = malloc(sizeof(int*) * nbcase);
  for(i=0; i<nbcase; i++)
    {
      v[i] = malloc(sizeof(int*) * nbcase);
      for(j=0; j<nbcase; j++)
	{
	  v[i][j] = 0;
	}
    }

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

  while(l != NULL)//On place tous les elements de la Bordure dans la pile
    {
      fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
      empile(&p, l->i, l->j);
      v[l->i][l->j] = 1;
      l = l->next;
    }
  detruitListe(z->B[cl]); //On efface la bordure, on y ajoutera les element de la pile
  z->B[cl]=NULL;

  fprintf(stderr, "%s %d\tEntree de boucle\n", __FILE__, __LINE__ );

  while(p.e != NULL)
    {
      e = depile(&p); //Recuperation de l'element actuel et liberation pile
      i = e->i;
      j = e->j;
      fprintf(stderr, "%s %d\tFree(e)\n", __FILE__, __LINE__ );
      free(e);

      fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

      if(M[i][j] == cl) // Si l'elem est de la bonne couleur, on l'ajoute a la ZSG et on explore les environs
	{
	  fprintf(stderr, "%s %d\tAlentours \n", __FILE__, __LINE__ );
	  ajoute_Zsg(z, i, j); 
	  fprintf(stderr, "%s %d\tAlentours erreur de seg? \n", __FILE__, __LINE__ );
	  printf("\t\tI: %d \tJ: %d\n", i, j);

	  if(i>0){
	    printf("App %d %d\n", z->App[i-1][j], __LINE__);
	  }	
	  fprintf(stderr, "%s %d\tFin App 1\n", __FILE__, __LINE__ );

	  if(i< nbcase-1){
	    printf("App %d %d\n", z->App[i+1][j], __LINE__);
	  }
	  fprintf(stderr, "%s %d\n\tFin App 2", __FILE__, __LINE__ );

	  if(j>0){
	    printf("App %d %d\n", z->App[i][j-1], __LINE__);
	  }
	  fprintf(stderr, "%s %d\tFin App 3\n", __FILE__, __LINE__ );

	  if(j<nbcase-1){
	    printf("App %d %d\n", z->App[i][j+1], __LINE__);
	  }
	  fprintf(stderr, "%s %d\tFin App 4\n", __FILE__, __LINE__ );



	  if( (i > 0) && !(( ( v[i - 1][j] == 1) || (appartient_Zsg(z, i - 1, j))))) //A Droite
	    {	//Si la case n'est ni dans la pile ni dans la ZSG
	      fprintf(stderr, "%s %d\tA Droite \n", __FILE__, __LINE__ );
	      empile(&p, i - 1, j); //On l'empile
	      v[i-1][j] = 1;
	    }

	  if( (i < nbcase-1) && !((  v[i + 1][j] || (appartient_Zsg(z, i + 1, j))))) //A Gauche
	    {	//Si la case n'est ni dans la pile ni dans la ZSG
	      fprintf(stderr, "%s %d\tA Gauche \n", __FILE__, __LINE__ );
	      empile(&p, i + 1, j); //On l'empile
	      v[i+1][j] = 1;
	    }

	  if( (j < nbcase-1) && !( ( v[i][j + 1] || (appartient_Zsg(z, i, j + 1))))) //En Bas
	    {	//Si la case n'est ni dans la pile ni dans la ZSG
	      fprintf(stderr, "%s %d\tEn Bas \n", __FILE__, __LINE__ );
	      empile(&p, i, j + 1); //On l'empile
	      v[i][j+1] = 1;
	    }

	  if( (j > 0) && !( (v[i][j - 1] || (appartient_Zsg(z, i, j - 1))))) //En Haut
	    {	//Si la case n'est ni dans la pile ni dans la ZSG
	      fprintf(stderr, "%s %d\tEn Haut \n", __FILE__, __LINE__ );
	      empile(&p, i, j - 1); //On l'empile
	      v[i][j-1] = 1;
	    }
	  fprintf(stderr, "%s %d\tFin conds\n", __FILE__, __LINE__ );
	}
      else //Sinon on l'ajoute a la bordure
	{
	  fprintf(stderr, "%s %d\tBordure\n", __FILE__, __LINE__ );
	  ajoute_Bordure(z, i, j, M[i][j]);
	}

    } 	fprintf(stderr, "%s %d\tSortie de Boucle\n", __FILE__, __LINE__ );
  for(i=0; i<nbcase; i++)
    {
      free(v[i]);
    }
  free(v);

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
}

#endif 
