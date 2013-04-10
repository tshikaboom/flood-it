#ifndef LISTE_CASE_H
#define LISTE_CASE_H

typedef struct Liste_C {
  int i;
  int j;
  struct Liste_C *next;
} Liste_case;

/*
 * Initialise une liste vide et rend un pointeur
 */
Liste_case *liste_init();

/*
 * Rend vrai si la liste est vide
 */
int liste_vide(Liste_case *l);

/*
 * Ajoute un element qui contient les coordonnes i et j suivi de l'ancienne liste
 *  a une nouvelle liste et la renvoie
 */
Liste_case* liste_ajoute(Liste_case *oldListe, int i, int j);

/*
 * Libere tous les element de la liste
 */
void liste_detruit(Liste_case *l);

/*
 * Affiche le contenu de la liste en arg
 */
void liste_affiche(Liste_case *L);

/*
 * Rend vrai si l'element existe
 */
int liste_existe(Liste_case *l, int i,int j);


/*
 * Copie une premiere liste dans une deuxieme liste
 * new: pointeur de pointeur vers liste pour modifier la nouvelle liste
 */
void liste_copy(Liste_case *old, Liste_case **new);

#endif
