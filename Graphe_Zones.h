#ifndef GRAPHE_ZONES_H
#define GRAPHE_ZONES_H

typedef struct sommet Sommet;

/* Element d'une liste de Sommets */
typedef struct cellule_som {
  Sommet *sommet;
  struct cellule_som *suiv;
} Cellule_som;

struct sommet {
  int num; /* Numero du sommet (sert uniquement a l'affichage) */
  int cl; /* Couleur d'origine du sommet-zone */
  Liste_case cases; /* Listes des cases du sommet-zone */
  int nbcase_som; /* Nombre de cases de cette liste */

  Cellule_som *sommet_adj; /* Liste des pointeurs sur les sommets adjacents */


  int marque; /* Cet entier servira pour le marquage des sommets
		 dans les algorithmes de parcours: 0 non marque, 1 marque */

  Sommet *pere; /* Ce pointeur servira pour retenir un chemin
		   dans les algorithmes de parcours:
		   il servira a noter le Pere dans les parcours en largeur */
  
};

typedef struct graphe_zone {
  int nbsom;
  /* Nombre de sommets dans le graphe */
  Cellule_som *som;
  /* Liste chainee des sommets du graphe */
  Sommet ***mat;
  /* Matrice de pointeurs sur les sommets indiquant
     a quel sommet appartient une case (i,j) de la grille */
} Graphe_zone;



#endif
