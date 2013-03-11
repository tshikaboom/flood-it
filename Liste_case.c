#ifndef LISTECASEC
#define LISTECASEC

#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"



//Initialise une liste vide et rend un pointeur
Liste_case *init_liste()
{  Liste_case *e = NULL;
  e =(Liste_case*) malloc(sizeof(Liste_case));
  if(e == NULL)
    { //Verifie que le malloc a fonctionne
      exit(EXIT_FAILURE);
    }

  e->next=NULL; //Init liste suivante a NULL pour eviter une faute de segmentation
  
  return e;
}

//Rend vrai si la liste est vide
int liste_vide(Liste_case *l)
{
  return (l == NULL) ;
}


//Rend vrai si l'element existe
int existe(Liste_case *l, int i, int j)
{
	while(l != NULL)
	{
		if( (l->i == i) && (l->j == j))
		{
			return 1;
		}	
		l = l->next;
	}

	return 1;
}

//Ajoute un element qui contient les coordonnes i et j suivi de l'ancienne liste a une nouvelle liste et la renvoie 
Liste_case* ajouteListe(Liste_case *oldListe, int i, int j)
{
  Liste_case *uno = init_liste();
  uno->next = oldListe;
  uno->i = i;
  uno->j = j;
  
  return uno;
}

//Libere tous les element de la liste 
void detruitListe(Liste_case *l)
{//Libere touts les elements d'une liste
  Liste_case *e = l, *aux;
  while(e != NULL)
    {
      aux = e->next;
      free(e);
      e=aux;
    } 
}

//Affiche le contenu de la liste en arg
void afficheListe(Liste_case *L)
{
  Liste_case *l = L;
  while(l != NULL)
    {
      printf("%d %d\n", l->i, l->j);
      l = l->next;
    }
}


//Copie une premiere liste dans une deuxieme liste
void copyList(Liste_case *old, Liste_case **new) //Pointeur de pointeur vers liste pour modifier la nouvelle liste
{
	while(old != NULL)
	{
		*new = ajouteListe( *new, old->i, old->j);
		old = old->next;
	}
}

//Rend le nombre d'elements de la liste

#endif
