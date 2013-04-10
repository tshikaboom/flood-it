#ifndef ZONESC
#define ZONESC

#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"
#include "Zones.h"

/* Renvoie une nouvelle Zone et test le succes des allocations */
void init_Zones (int **M, Zones *newZone)
{
  int i, j;
  int a, b;

  
  newZone->Lzsg = NULL; /* Initialisation a NULL pour test du succes du malloc */
  newZone->B = NULL;
  newZone->App =  malloc(sizeof(int *) * newZone->nbcase);
  if (newZone->App == NULL) {
    fprintf(stderr, "Allocation de App failed!\n");
    exit(EXIT_FAILURE);
  }
  
  for (i=0; i<newZone->nbcase; i++) {
    newZone->App[i] =  malloc(sizeof(int) * newZone->nbcase); 
    for(j=0; j < newZone->nbcase; j++)
      newZone->App[i][j] = -2;
  }

  for (a=0; a<newZone->nbcase; a++)
      newZone->App[0][a] = -2;

  for (a=0; a<newZone->nbcase; a++) {
    for (b=0; b<newZone->nbcase; b++)
      printf("%d\t", newZone->App[a][b]);
    printf("\n");
  }

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

  newZone->B = malloc(sizeof(Liste_case *) * newZone->nbcl);
  if (newZone->B == NULL) {
    fprintf(stderr, "Allocation de B failed!\n");
    exit(EXIT_FAILURE);
  }
  for(i=0; i < newZone->nbcl; i++)
      newZone->B[i] = NULL;

  newZone->Lzsg = (Liste_case *) malloc(sizeof(Liste_case));


  if ( (newZone->Lzsg == NULL) || (newZone->B == NULL))
      exit(EXIT_FAILURE);

  /* Valeurs de demarrage */
  ajoute_Zsg(newZone, 0, 0);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  ajoute_Bordure(newZone, 0, 1, M[0][1]);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  ajoute_Bordure(newZone, 1, 0, M[1][0]);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  ajoute_Bordure(newZone, 1, 1, M[1][1]);
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );


}

/* Ajoute une element a la liste des Zsg et modifide App */
void ajoute_Zsg(Zones *z, int i, int j)
{
  if (i > z->nbcase || j > z->nbcase)
    exit(EXIT_FAILURE);

  if (z->App[i][j] != -1) {

    /* Remplace la liste par une nouvelle liste contenant la case supplemantaire */
    z->Lzsg =  ajouteListe(z->Lzsg, i, j); 

    /* Remplace la reference a la liste dans le tableau App */
    z->App[i][j] = -1;
  }
}

/* Ajoute un element a la bordure et change sa reference dans App avec cl */
void ajoute_Bordure(Zones *z, int i, int j, int clCase)
{
  if (i > z->nbcase || j > z->nbcase)
      exit(EXIT_FAILURE);

  /* Remplace la liste par une nouvelle liste contenant la case supplemantaire */
  z->B[clCase] =  ajouteListe(z->B[clCase], i, j); 

  /* Remplace la reference a la liste dans le tableau App */
  if (clCase<100)
    z->App[i][j] = clCase;



}

/* Renvoie vrai si la case appartient a la Bordure */
int appartient_Bordure_coord(Zones *z, int i, int j)
{
  /* Si la ref dans App correspond a une couleur, elle appartient a la bordure et est plus grande que 0 */
  return (z->App[i][j] > 0);
}

/* Renvoie vrai si la case appartient a la Zsg */
int appartient_Zsg(Zones *z, int i, int j)
{
  /* Si la ref dans App est egale a -1, (i,j) est presente dans la Zsg */
//  printf("App:\t%d\n", z->App[i][j]);
  return (z->App[i][j] == -1);
}

/* Renvoie vrai si la couleur est presente dans la bordure */
int appartient_Bordure(int ** M, Zones *z, int cl)
{
  Liste_case *l = NULL;
  l = z->B[cl];
  int i,j;

  while(1) {
    if (l == NULL)
      return 0;
    i = l->i;
    j = l->j;
    
    if (M[i][j] == cl)
      return 1;
    
    l = l->next;
  }
}

void colorieZone (int **M, Zones *Z, int cl, int *cpt)
{
  Liste_case *e = Z->Lzsg;
  int i, j;
  *cpt = 0; /* init du compteur */
  while(e != NULL) {
    i = e->i;
    j = e->j;

    if ((i < Z->nbcase) && (j < Z->nbcase))
      M[i][j] = cl;

    e = e->next; 

    (*cpt)++;
  }

}
void aggranditZone(int ** M, Zones *z, int cl)
{
  int i, j, nbcase = z->nbcase;
  int **v;
  Pile p;
  /* p-> cases a visiter, v cases visitees.
     Si v[i][j] == 1, la case (i,j) ne dois pas etre empilee */
  Element *e = NULL;
  Liste_case *l = z->B[cl];
  init_pile(&p);

  /* allocation de v */
  v = malloc(sizeof(int*) * nbcase);
  for (i=0; i<nbcase; i++) {
    v[i] = malloc(sizeof(int *) * nbcase);

    /* initialisation de v */
    for (j=0; j<nbcase; j++)
      v[i][j] = 0;
  }



  while(l != NULL) { /* On place tous les elements de la Bordure dans la pile */
    empile(&p, l->i, l->j);
    v[l->i][l->j] = 1;
    l = l->next;
  }
  
  detruitListe(z->B[cl]); /* On efface la bordure, on y ajoutera les element de la pile */
  z->B[cl]=NULL;

  while(p.e != NULL) {
    e = depile(&p); /* Recuperation de l'element actuel et liberation pile */
    i = e->i;
    j = e->j;
    free(e);

    if (M[i][j] == cl) {
      /* Si l'elem est de la bonne couleur,
	 on l'ajoute a la ZSG et on explore les environs */
      ajoute_Zsg(z, i, j); 
	
      /* a gauche */
      if ((i > 0) &&
	  !((v[i - 1][j] == 1) || (appartient_Zsg(z, i - 1, j)))) {
	/* Si la case n'est ni dans la pile ni dans la ZSG */
	empile(&p, i - 1, j); /* On l'empile */
	v[i-1][j] = 1;
      }

      /* a droite */
      if ((i < nbcase-1) &&
	  !(v[i + 1][j] || (appartient_Zsg(z, i + 1, j)))) {
	/* Si la case n'est ni dans la pile ni dans la ZSG */
	empile(&p, i + 1, j);
	v[i+1][j] = 1;
      }

      /* en bas */
      if ((j < nbcase-1) &&
	  !( v[i][j + 1] || (appartient_Zsg(z, i, j + 1)))) {
	/* Si la case n'est ni dans la pile ni dans la ZSG */
	empile(&p, i, j + 1);
	v[i][j+1] = 1;
      }

      /* en haut */
      if ((j > 0) &&
	  !(v[i][j - 1] || (appartient_Zsg(z, i, j - 1)))) {
	/* Si la case n'est ni dans la pile ni dans la ZSG */
	empile(&p, i, j - 1);
	v[i][j-1] = 1;
      }
    }
    else /* Sinon on l'ajoute a la bordure */
	ajoute_Bordure(z, i, j, M[i][j]);

  }

  
  for(i=0; i<nbcase; i++)
      free(v[i]);


  free(v);

}

#endif 
