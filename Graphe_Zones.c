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

/*
void trouve_zone(int **M, i, j, Sommet *s)
{
*/
