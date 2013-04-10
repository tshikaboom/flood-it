#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"
#include "Zones.h"
#include "Graphe_Zones.h"


Cellule_som *ajoute_liste_sommet(Sommet *ptrsommet, Cellule_som *cell_som)
{
  Cellule_som *nvlcell;

  nvlcell = (Cellule_som *) malloc(sizeof(Cellule_som));

  nvlcell->sommet = ptrsommet;
  nvlcell->suiv = cell_som;


  return nvlcell;

}

void detruit_liste_sommet(Cellule_som *cell_som)
{
  Cellule_som *ptr_courant = cell_som;
  while (ptr_courant) {
    cell_som = ptr_courant->suiv;

    free(ptr_courant);

    ptr_courant = cell_som;
  }
}


void ajoute_voisin(Sommet *s1, Sommet *s2)
{
  s1->sommet_adj = ajoute_liste_sommet(s2, s1->sommet_adj);
  s2->sommet_adj = ajoute_liste_sommet(s1, s2->sommet_adj);
}

/* bool adjacent(s1, s2)
 * fonction pour determiner l'adjacence de deux sommets
 * dans un graphe
 * -> rend 1 si s1 est inclus dans s2
 * -> rend 2 si s2 est inclus dans s1
 * -> rend 3 si double-inclusion
 * -> rend 0 si aucune inclusion
 */
int adjacent(Sommet *s1, Sommet *s2)
{
  int bool=0;
  Cellule_som *ptr_courant = s1->sommet_adj;
  
  while (ptr_courant->sommet != NULL)
    if (ptr_courant->sommet == s2) {
      bool=1;
      
      break; // on saute le while car on a trouve une inclusion
    }
    else ptr_courant = ptr_courant->suiv;
  
  
  ptr_courant = s2->sommet_adj;
  while (ptr_courant->sommet != NULL)
    if (ptr_courant->sommet == s1) {
      if (bool==1) bool=3; // double-inclusion
      else bool=2; // s2 inclus dans s1
      
      break; // on saute le while car on a trouve une inclusion
    }
    else ptr_courant = ptr_courant->suiv;
  
  return bool;
}

void cree_graphe_zone(int** M, int nbCases, Graphe_Zone G)
{
  int i, j;

  for(i = 0; i < nbCases; i++)
    {
      for(j = 0; j < nbCases; j++)
	{
	  if(G->mat[i][j] == NULL){
	    Sommet s = malloc(sizeof(Sommet)); //Sommet vide pense a tout initaliser
	    s.nbcase_som = 0;
	    s.cases->next = NULL;
	    trouve_zone(M, i, j, &s, G, nbCases);
	  }
	}
    }
}

void trouve_zone(int **M, i, j, sommet *s, Graphe_Zone G, int nbCases)
{

  /* Pile_case pileun; */
  /* init_pile(&pileun); */
  /* Pile_case piledeux= NULL; */
  /* int nb = 0; */
  /* s->cl = M[i][j]; */

  /* empile(&p, i, j); */
  /* ajouteListe((&s->suiv), i, j); */

  s->cl = M[i][j]; //Mise a jour de la couleur de la case
  detruit_liste_sommet(&(s->sommet_adj)); //Suppresion des membres de la zone
  s->nbCases = 0;
  Pile_case p;
  init_pile(&p);
  empile(&p, i, j); //On empile la premiere case
  
  while(! liste_vide(&p))
    {
      Element e = depile(&p);
      int i = e->i, j = e->j; //On depile et recupere l'elem courant
      
      if(((e->j+1) < nbCases) && (M[e->i][e->j] == s->cl) && ( !existePile(&p, e->i, e->j+1)) && ( !appartient_liste(s->cases, e->i, e->j+1))){
	ajoute_liste((s->cases), e->i, e->j+1);//Ajout de la case a la liste des membres de la zone
	s->nbcase_som++; //Incr du compteur de zone
	empile(&p, e->i, e->j+1); 
      }
  
      if(((e->j-1) >= 0) && (M[e->i][e->j] == s->cl)  && ( !existePile(&p, e->i, e->j+1))&& ( !appartient_liste(s->cases, e->i, e->j-1))){
	ajoute_liste((s->cases), e->i, e->j-1);
	s->nbcase_som++;
	empile(&p, e->i, e->j-1);
      }

      if(((e->i+1) < nbCases) && (M[e->i][e->j] == s->cl)  && ( !existePile(&p, e->i, e->j+1))&& ( !appartient_liste(s->cases, e->i+1, e->j))){
	ajoute_liste((s->cases), e->i+1, e->j);
	s->nbcase_som++;
	empile(&p, e->i+1, e->j);
      }

      if(((e->i-1) >= 0) && (M[e->i][e->j] == s->cl)  && ( !existePile(&p, e->i, e->j+1)) && ( !appartient_liste(s->cases, e->i-1, e->j))){
	ajoute_liste((s->cases), e->i-1, e->j);
	s->nbcase_som++;
	empile(&p, e->i-1, e->j);
      }

      //On pointe la case de la matrice de G sur la zone
      G->matt[i][j] = s;
      G->som++;

      free(e);
      
    }
  free(p);

}