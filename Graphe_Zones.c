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

  // donc la nouvelle tete de liste est la cellule qu'on vient de rajouter
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

  while (ptr_courant)
    if (ptr_courant->sommet == s2) {
      bool=1;

      break; // on saute le while car on a trouve une inclusion
    }
    else ptr_courant = ptr_courant->suiv;


  ptr_courant = s2->sommet_adj;
  while (ptr_courant)
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
  // ici on considere G->som = NULL de base

  // allocation des sommets de G
  for (i=0; i<nbCases; i++)
    for (j=0; j<nbCases; j++)
      if (G->mat[i][j] == NULL) {
	s = (Sommet *) malloc(sizeof(Sommet)); // initalisation d'un sommet vide
	s->nbcase_som = 0;
	s->cases = liste_init();
	s->sommet_adj = NULL;
	G->mat[i][j] = s;
	(G->nbsom)++;

	/* ceci marche meme si G->som n'a pas de liste a la base
	 * donc le "dernier" element sera a NULL
	 */
	G->som = ajoute_liste_sommet(s, G->som);

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
	  // si les sommets sont adjacents, on skip
	  if (s == s2 || adjacent(s, s2) != 0)
	    continue;

	  // Si les sommets sont diff et qu'ils ne sont pas deja adjacents
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

  while (!pile_vide(p)) {
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

// bool bordure_dans_bordure?
int sommet_dans_bordure(Cellule_som *sommet, Bordure *bordure)
{
  Cellule_som *parcours = bordure->tab[sommet->sommet->cl];

  while (parcours) {
    if (parcours->sommet->num == sommet->sommet->num) return 1; // on a trouve
    parcours = parcours->suiv;
  }


  // on n'a rien trouve
  return 0;
}

Cellule_som *plusCourtChemin(Graphe_zone *G, int nbCases)
{
  int i = 0;
  Sommet
    *depart = G->mat[0][0],
    *destination = G->mat[nbCases-1][nbCases-1];
  Cellule_som *chemin = ajoute_liste_sommet(depart, NULL);

  if(adjacent(depart, destination) != 0)
    {
      chemin = ajoute_liste_sommet(destination, chemin);
      return chemin;
    }

  return recPlusCourt(G, chemin, depart, destination, 1, &i);
}
/* depart = Sommet de depart, case actuelle
 * destination = Sommet a atteindre
 * marqueur: indice incremente a chaque nouvelle generation 
 * chemin = chemin parcourus pour atteindre la destination
 * retour -> nombre de cases dans le chemin
 * distance: nombre d'etapes pour arriver a la destination
 */
Cellule_som *recPlusCourt(Graphe_zone *G, Cellule_som *chemin, Sommet *depart, Sommet *destination, int marqueur, int *distance)
{
  int i = 0, j;
  Cellule_som
    *voieMin = NULL,
    *voieSnd = NULL,
    *adjListe = depart->sommet_adj;

  /*	if(depart == destination)
	{
	destination->marque = marqueur;
	*distance = 1;
	return ajoute_liste_sommet(destination, chemin);
	}*/
  if (adjacent(depart, destination) != 0) {
    if ((destination->marque != 0) &&
	(destination->marque < marqueur )) { //Il existe un chemin plus court
	  *distance = 1000; // hmmm..
	  return NULL;
	}

    destination->marque = marqueur;
    depart->marque = marqueur;
    *distance = 2;
    return ajoute_liste_sommet(destination, ajoute_liste_sommet(depart, chemin));
    }
  else
    {
      while (adjListe != NULL && i == 0) //Pour le premier tour
	{
	  if ((adjListe->sommet->marque == 0) ||
	      (adjListe->sommet->marque > marqueur ))
	    { //Sommet non visite ou par une generation plus recente de recPlusCourt
	      voieMin = recPlusCourt(G,  ajoute_liste_sommet(depart, chemin), adjListe->sommet, destination, marqueur + 1, &i);
	    }
	  adjListe = adjListe->suiv;
	}
      while(adjListe != NULL)
	{
	  if( (adjListe->sommet->marque == 0) ||
	      (adjListe->sommet->marque > marqueur ))
	    {
	      voieSnd = recPlusCourt(G,  ajoute_liste_sommet(depart, chemin), adjListe->sommet, destination, marqueur + 1, &j);

	      if(j < i) //Le chemin courant est plus court que le dernier chemin le plus court
		{
		  i = j;
		  voieMin = voieSnd;
		}
	    }

	  adjListe = adjListe->suiv;
	}
    }

  if(voieMin != NULL) //Si on a un resultat valable
    {
      *distance = i  + 1;
      return voieMin;	
    } else {
    *distance = 1000;
    return NULL;
  }
}

/*
 *	Mise a jour de la bordure graphe
 *	Changement des couleurs et des adjacences des membre du Graphe
 */
void update_bordure_graphe(Graphe_zone *G, int **M, int nbCl)
{
  int i, j, iMax = 0;
  int *tab = NULL;
  Cellule_som *bordureElem = NULL;
  Cellule_som *a = G->mat[0][0]->sommet_adj; //recuperation de la liste des zones de bordure
  Cellule_som *temp = a; // deux elements Cellule_Som* pour suppression quoi. genre double-parcoureurs
  Sommet *Zsg = G->mat[0][0];
  Liste_case *casesAAjouter = NULL, *elem = NULL;

  tab = malloc(sizeof(int) * nbCl);
  assert(tab != NULL);

  for(i = 0; i < nbCl; i++)
    {
      tab[i] = 0;
    }

  while(a != NULL)
    {
      tab[(a->sommet)->cl]++;
      a = a->suiv;
    }
  for(i = 1; i < nbCl; i++)
    {
      iMax = tab[i] > tab[iMax] ? i : iMax;
    }
  //iMax -> indice de la couleur la plus presente = valeur de la couleur
  changeCouleurZsg(G, M, iMax);

  //On supprime toutes les zones de la bordure de la meme couleur que iMax
  //On ajoute a la zsg les cases des zones supprimees et leurs adjacences
  //on a le nombre de zones dans tab[iMax]

  a = (G->mat[0][0])->sommet_adj;
  elem = Zsg->cases;
  while(elem->next != NULL)
    {
      elem = elem->next;
    }

  while(a != NULL)
    {	
      if((a->sommet)->cl == iMax)
	{
	  bordureElem = a->sommet->sommet_adj;
	  while(bordureElem != NULL)//Ajout des adjacences
	    {
	      ajoute_voisin(a->sommet, bordureElem->sommet);
	      bordureElem = bordureElem->suiv;
	    }	
	  //On enleve a de la liste d'adjacence de Zsg

	  //Recuperation des cases
	  casesAAjouter = a->sommet->cases;
	  elem->next = casesAAjouter;
	  while(elem->next != NULL)
	    {
	      i = elem->i;//Ajoute de Zsg dans la matrice de Sommets
	      j = elem->j; //Pour les nouvelles cases
	      G->mat[i][j] = Zsg;
	      elem = elem->next;
	    }

	  //Destruction du sommet
	  temp->suiv = a->suiv;
	  free(a);
	  a = temp->suiv;
	  G->nbsom--; //On a supprime un sommet
	  //On le retire du compteur

	}
      else {
	//Destruction du sommet
	temp = a;
	a = a->suiv;
      }
    }
}
/* On prend un graphe et une couleur
 *	On change la couleur du sommet de la Zsg
 *	On parcourt toutes les cases de la Zsg et on leur donne leur nouvelle couleur
 */
void changeCouleurZsg(Graphe_zone *G, int ** M,  int cl)
{
  Liste_case *elem = (G->mat[0][0])->cases;
  int i, j;
  (G->mat[0][0])->cl = cl;

  while(elem != NULL)
    {
      i = elem->i;
      j = elem->j;
      M[i][j] = cl;
      elem = elem->next;
    }
}
