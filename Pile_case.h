#ifndef PILE_CASE_H
#define PILE_CASE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  struct Element_pile * e;
} Pile;

typedef struct Element_pile {
  int i;
  int j;
  struct Element_pile * next;
} Element;


/*
 * Initialisation de la pile passe en argument
 */
void init_pile(Pile *p);

/*
 * Bool pile_vide?
 */
int pile_vide(Pile p);

/*
 * Ajoute un element contenant les deux entiers en tete de la pile
 */
void empile(Pile *p, int i, int j);


/*
 * Rend un pointeur vers l'element de tete de la pile et le supprime de celle-ci
 */
Element* depile(Pile *p);

/*
 *Rend vrai si l'element existe
 */
int existePile(Pile *l, int i,int j);

#endif
