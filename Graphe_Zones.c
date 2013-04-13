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

//Ajoute les deux sommets dans leurs listes d'adjacence respectives
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

void cree_graphe_zone(int** M, int nbCases, Graphe_zone *G)
{
  int i, j;
  Sommet *s = NULL, *s2 = NULL;
  Cellule_som *l = NULL;

  // allocation des sommets de G
  for (i=0; i<nbCases; i++)
      for (j=0; j<nbCases; j++)
	  if (G->mat[i][j] == NULL) {
	    s = malloc(sizeof(Sommet)); // initalisation d'un sommet vide
	    s->nbcase_som = 0;
	    s->cases->next = NULL;
	    s->sommet_adj = NULL;

	    (G->nbsom)++;

	    l = malloc(sizeof(Cellule_som)); //Chainage des Sommets du graphe
	    assert(l != NULL);
	    l->suiv = G->som;
	    G->som = l;
	    l=NULL;

	    // on remplit les sommets en appelant trouve_zone
	    trouve_zone(M, i, j, s, G, nbCases);
	  }


  // recherche des sommets adjacents
  for (i=0; i < nbCases; i++)
    {
      for(j=0; j < (nbCases - 1); j++)
	/* Si deux cases adjacentes de la matrice pointent vers des Sommets
	 * differents qui ne sont pas deja adjacents alors une relation
	 * d'adjacence est ajoutée. Sinon, on passe aux cases suivantes
	 */
	{
	  s = G->mat[i][j];
	  s2 = G->mat[i][j+1];
	  if (s == s2 || adjacent(s, s2) != 0)
	      continue;

	  //Si les sommets sont diff et qu'ils ne sont pas deja adjacents
	  ajoute_voisin(s, s2);
	}
    }
}

void trouve_zone(int **M, int i, int j, Sommet *s, Graphe_zone *G, int nbCases)
{
  Pile p;
  Element *e;
  /* Pile_case pileun; */
  /* init_pile(&pileun); */
  /* Pile_case piledeux= NULL; */
  /* int nb = 0; */
  /* s->cl = M[i][j]; */

  /* empile(&p, i, j); */
  /* liste_ajoute((&s->suiv), i, j); */

  s->cl = M[i][j]; // Mise a jour de la couleur de la case
  detruit_liste_sommet(s->sommet_adj); // Suppresion des membres de la zone
  s->nbcase_som = 0;


  init_pile(&p);
  
  empile(&p, i, j); // On empile la premiere case
  
  while(!pile_vide(p)) {
    e = depile(&p);
    i = e->i, j = e->j; // On depile et recupere l'elem courant

    
    if ((e->j+1 < nbCases) &&
	(M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!liste_existe(s->cases, e->i, e->j+1))) {
      liste_ajoute(s->cases, e->i, e->j+1); // Ajout de la case a la liste des membres de la zone
      s->nbcase_som++; // Incr du compteur de zone
      empile(&p, e->i, e->j+1);
    }
  
    if ((e->j-1 >= 0) &&
	(M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!liste_existe(s->cases, e->i, e->j-1))) {
      liste_ajoute(s->cases, e->i, e->j-1);
      s->nbcase_som++;
      empile(&p, e->i, e->j-1);
    }

    if ((e->i+1 < nbCases) &&
	(M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!liste_existe(s->cases, e->i+1, e->j))) {
      liste_ajoute(s->cases, e->i+1, e->j);
      s->nbcase_som++;
      empile(&p, e->i+1, e->j);
    }

    if ((e->i-1 >= 0) && (M[e->i][e->j] == s->cl) &&
	(!pile_existe(&p, e->i, e->j+1)) &&
	(!liste_existe(s->cases, e->i-1, e->j))) {
      liste_ajoute((s->cases), e->i-1, e->j);
      s->nbcase_som++;
      empile(&p, e->i-1, e->j);
    }

    //On pointe la case de la matrice de G sur la zone
    G->mat[i][j] = s;
    G->som++;

    free(e);
      
  }
  //  free(p);

}

void affichage_graphe(Graphe_zone *G, int nbCases)
{
  int i=0, j=0;
  Cellule_som *parcours; // sert a parcourir la liste des sommets

  for (i=0; i<nbCases; i++)
    for (j=0; j<nbCases; j++) {
      parcours = G->mat[i][j]->sommet_adj;
      printf("Dans le sommet [%d][%d], on a les noeuds ", i, j);
      while (parcours) {
	printf("%d ", parcours->sommet->num);
	parcours = parcours->suiv;
      }
      printf("\n");
    }

}

Bordure *bordure_init(int nbcl)
{
  int i;
  Bordure *nvbordure;

  // allocation de nvbordure
  nvbordure = (Bordure *) malloc(sizeof(Bordure));
  if (!nvbordure) return NULL;

  // allocation du tableau de listes
  nvbordure->tab = (Cellule_som **) malloc(nbcl*sizeof(Cellule_som *));
  if (!(nvbordure->tab)) return NULL;

  // initialisation du tableau de listes
  for (i=0; i<nbcl; i++) nvbordure->tab[i] = NULL;

  // allocation du tableau des tailles de listes
  nvbordure->taille_liste = (int *) malloc(nbcl*sizeof(int));
  if (!(nvbordure->taille_liste)) return NULL;
  
  // initialisation du tableau des tailles de listes
  for (i=0; i<nbcl; i++) nvbordure->taille_liste = 0;


  nvbordure->nbcl = nbcl;

  return nvbordure;

}
