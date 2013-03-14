#ifndef LISTE_CASE_H
#define LISTE_CASE_H

typedef struct Liste_C{
  int i;
  int j;
  struct Liste_C *next;
}Liste_case;

//Initialise une liste vide et rend un pointeur
Liste_case *init_liste();


//Rend vrai si la liste est vide
int liste_vide(Liste_case *l);

//Ajoute un element qui contient les coordonnes i et j suivi de l'ancienne liste a une nouvelle liste et la renvoie 
Liste_case* ajouteListe(Liste_case *oldListe, int i, int j);

//Libere tous les element de la liste 
void detruitListe(Liste_case *l);

//Affiche le contenu de la liste en arg
void afficheListe(Liste_case *L);

//Rend vrai si l'element existe
int existe(Liste_case *l, int i,int j);


//Copie une premiere liste dans une deuxieme liste
void copyList(Liste_case *old, Liste_case **new); //Pointeur de pointeur vers liste pour modifier la nouvelle liste

#endif
