#include "Pile_case.h"

//Initialise la pile passe en arg
void init_pile(Pile *p)
{
  p->e = NULL;
}

//Bool pile_vide?
int pile_vide(Pile p)
{
  return p.e == NULL;
}

//Ajoute un element contenant les deux entiers en tete de la pile
void empile(Pile *p, int i, int j)
{
  Element *elem = (Element*) malloc(sizeof(Element));
  elem->next = p->e;
  p->e = elem;
  (p->e)->i = i;
  (p->e)->j = j;
}

//Rend un pointeur vers l'element de tete de la pile et le supprime de celle-ci
Element* depile(Pile *p)
{
  if (p->e == NULL) {
      fprintf(stderr, "Pile vide!\n");
      exit(EXIT_FAILURE);
    }

  Element *tmp = p->e;
  p->e = tmp->next;
  return tmp;
}

//Rend vrai si l'element existe
int pile_existe(Pile *l, int i, int j)
{
  Element *elem = l->e;
  while (elem != NULL) {
    if (elem->i == i && elem->j == j)
      return 1;   
    elem = elem->next;
  }

  return 0;
}
