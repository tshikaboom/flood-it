#ifndef PILEC
#define PILEC

#include "Pile_case.h"

//Initialise la pile passe en arg
void init_pile(Pile *p)
{
  p->e =  NULL;
}

//Bool pile_vide?
int pile_vide(Pile p)
{
  return  p.e == NULL;
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

//Rend un element de la pile dans et deux entiers et le supprime
/*
  void depile(Pile *p, int* i, int* j)
  {
  *i = (p->e)->i;
  *j = (p->e)->j;

  Element* now = p->e;
  p->e = (p->e)->next;
  free(now);
  } */

//Rend un pointeur vers l'element de tete de la pile et le supprime de celle-ci
Element* depile(Pile *p)
{
  if(p->e == NULL)
    {
      fprintf(stderr, "Pile vide!\n");
      exit(EXIT_FAILURE);
    }

  Element *tmp = p->e;
  p->e = tmp->next;
  return tmp;
}

//Rend vrai si l'element existe
int existePile(Pile *l, int i,int j)
{
  printf(" %s %d\texistePile \n", __FILE__, __LINE__); 
  
  Element *elem = l->e;
  while(elem != NULL)
    {
      if( elem->i == i && elem->j == j)
	return 1;

      elem = elem->next;
    }

  printf("%s %d\t\tExit existePile\n", __FILE__, __LINE__);
  return 0;
}

#endif
