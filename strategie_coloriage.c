#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strategie_coloriage.h"
#include "Flood-It-1.h"

void colorie_zone_imp(int ** tab, int i, int j, int cl, int* taille, int nbCases)
{
  Pile p; /* Pile des cases a modifier */
  init_pile(&p);
  int **matriceIncr; /* matrice servant a incrementer la taille */
  int compteur, compteur2;
  Element *e = NULL; /* Case actuelle */

  int couleurActuelle = tab[i][j]; /* Memorisation de la couleur avant changement */

  matriceIncr = (int **) malloc(nbCases*sizeof(int *));
  for (compteur=0; compteur<nbCases; compteur++)
    matriceIncr[compteur] = (int *) malloc(nbCases * sizeof(int));


  for (compteur=0; compteur<nbCases; compteur++)
    for (compteur2=0; compteur2<nbCases; compteur2++)
      matriceIncr[compteur][compteur2] = 0;
  
  printf("wat?\n");  
  printf("debut colorie_imp: taille %d etc\n", *taille);

  /* Evite les boucles infinies si la case a deja la couleur demandee */
  if (cl == couleurActuelle)
    return;

  empile(&p, i , j); /* Avant d'entamer la boucle empilement de la premiere case */
  matriceIncr[i][j] = 1;
  *taille = *taille + 1;

  *taille = 0;
  printf("nbcases au carre: %d\n", nbCases*nbCases);
  while(! pile_vide(p)) /* Tant que la pile n'est pas vide */
    {
      e = depile(&p); /* On recupere une nouvelle case actuelle */

      i = e->i; /* Memorisation des coordonnes de la couleur actuelle */
      j = e->j;
      tab[i][j] = cl; /* Changement de la couleur de l'element actuel */

      /* Verification des couleurs des cases environnantes */
      if (i-1 >= 0 && (couleurActuelle == tab[i-1][j])) { /* A gauche */
	if (matriceIncr[i-1][j] == 0) {
	  *taille = *taille+1;
	  matriceIncr[i-1][j] = 1;
	}
	empile(&p, (i-1), j); /* On empile une prochaine case */

      }
	  
      if (j-1 >= 0 && (couleurActuelle == tab[i][j-1])) { /* Au dessus */
	if (matriceIncr[i][j-1] == 0) {
	  *taille = *taille+1;
	  matriceIncr[i][j-1] = 1;

	}
	empile(&p, i, (j - 1)); /* On empile une prochaine case */
      }
		
      if (i+1 < nbCases && (tab[i+1][j] == couleurActuelle)) { /*  A droite */
	if (matriceIncr[i+1][j] == 0) {
	  *taille = *taille+1;
	  matriceIncr[i+1][j] = 1;

	}
	empile(&p, (i+1), j); /* On empile une prochaine case */
      }
	    
      if (j+1 < nbCases && (tab[i][j+1] == couleurActuelle)) { /* En dessous */
	if (matriceIncr[i][j+1] == 0) {
	  *taille = *taille+1;
	  matriceIncr[i][j+1] = 1;

	}
	empile(&p, i, (j+1)); /* On empile une prochaine case */
      }


      printf("fin colorie_imp: taille %d\n", *taille); 
      free(e); /* liberation de la case actuelle */

    }

}


void colorie_zone_rec(int ** tab, int i, int j, int cl, int* taille, int nbCases)
{
  int couleurActuelle = tab[i][j]; /* Memorisation de la couleur avant changement */

  /* Changement de la couleur avant l'appel recursif pour eviter les boucles infinies */

  tab[i][j] = cl;

  if(cl == couleurActuelle) /* Evite les boucles infinies si la case a deja la couleur demandee */
    {
      return;
    }

  /* Verification des couleurs des cases environnantes */
  if( (i > 0) && (couleurActuelle == tab[i-1][j])) /* a gauche */
    {
      fprintf(stderr, "Going to: i->%d j->%d\n", (i - 1), j);
      colorie_zone_rec(tab, (i-1), j, cl, taille, nbCases);
    }

  if( (j > 0) && (couleurActuelle == tab[i][j-1])) /* au dessus */
    {
      fprintf(stderr, "Going to: i->%d j->%d\n", i, (j - 1));
      colorie_zone_rec(tab, i, (j-1), cl, taille, nbCases);
    }
  if( (i < (nbCases - 1)) && (tab[i+1][j] == couleurActuelle)) /* a droite */
    {
      fprintf(stderr, "Going to: i->%d j->%d\n", (i + 1), j);
      colorie_zone_rec(tab, (i+1), j, cl, taille, nbCases);
    }

  if( (j < (nbCases - 1)) && (tab[i][j+1] == couleurActuelle)) /* en dessous */
    {
      fprintf(stderr, "Going to: i->%d j->%d\n", i, (j + 1));
      colorie_zone_rec(tab, i, (j+1), cl, taille, nbCases);
    }


  (*taille)++;
}



int strategie_aleatoire_imp(Grille* G, int ** tab, int nbCases, int nbCl)
{
  srand(time(NULL)); /* Generation de la graine */
  int r, i, j, taille = 0, cpt = 0;
  printf("nbCases %d \n", nbCases);
  while(taille < nbCases*nbCases-1){


    r = rand() % nbCl; /* Initialisation de la couleur aleatoire € [0;nbCl[ */
    colorie_zone_imp(tab, 0, 0, r, &taille, nbCases);	
    printf(" ->%d  ", taille);
    for (i=0;i<nbCases; i++ )
      for (j=0;j<nbCases ;j++)
	Grille_chg_case(G,i,j,tab[i][j]);

    Grille_redessine_Grille();
      
    cpt++;
    Grille_attente_touche();
  }

  return cpt;
}


int strategie_aleatoire_rec(Grille* G, int ** tab, int nbCases, int nbCl)
{
  srand(time(NULL)); /* Generation de la graine */
  int r, i, j, taille = 0, cpt = 0;

  while(taille < (nbCases * nbCases))
    {
      taille = 0; /* initialisation du compteur */
      r = rand() % nbCl; /* Initialisation de la couleur aleatoire € [0;nbCl[ */
      colorie_zone_rec(tab, 0, 0, r, &taille, nbCases);	

      for (i=0;i<nbCases; i++ )
	{
	  for (j=0;j<nbCases;j++)
	    {
	      Grille_chg_case(G,i,j,tab[i][j]);
	    }
	}
      Grille_redessine_Grille();

      Grille_attente_touche();

      cpt++;
    }

  return cpt;
}


int strategie_aleatoire_rapide(Grille* G, int ** tab, int nbCases, int nbCl)
{
  srand(time(NULL)); /* Generation de la graine */
  int r, i, j, taille = 0, cpt = 0;

  Zones z;
  z.nbcase = nbCases; 
  z.nbcl = nbCl;
  init_Zones(tab, &z); 

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

  while(taille < ((nbCases * nbCases)-4)) {

      taille = 0; /* initialisation du compteur */
      r = rand() % nbCl; /* Initialisation de la couleur aleatoire € [0;nbCl[ */

      
      /* Si la ZSG est deja de cette couleur
	 ou qu'aucune case de la bordure ne l'est */      
      if(r == tab[0][0] || z.B[r] == NULL)	
	continue; /* Evite les iterations inutiles */
	

      colorieZone(tab, &z, r, &taille);	
      fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

      aggranditZone(tab, &z, r);	
      fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

      for (i=0;i<nbCases; i++ )
	{
	  for (j=0;j<nbCases;j++)
	    {
	      Grille_chg_case(G,i,j,tab[i][j]);
	    }
	}
      Grille_redessine_Grille();

      Grille_attente_touche();

      cpt++;
      fprintf(stderr, "%s %d %d %d\n", __FILE__, __LINE__, taille, nbCases );
    }

  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
  /* liste_detruit(z.B);  --> Boucle infinie */
  /* z.B = NULL; */
  liste_detruit(z.Lzsg);
  z.Lzsg = NULL;
  fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

  return cpt;
}
