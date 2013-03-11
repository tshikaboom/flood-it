#ifndef FLOODIT1H
#define FLOODIT1H


#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Pile_case.h"
#include "Liste_case.h"
#include "Zones.h"

//Colorie la case (i,j) et la zone environnante, appel recursif si les cases autour sont de la meme couleur que la case visee
//Incremente un compteur du nombre de casses changees
//ARGS: matrice, colonne, ligne, couleur, pointeur vers taille, taille de la matrice
void colorie_zone_rec(int ** tab, int i, int j, int cl, int* taille, int nbCases);

/*	
 *	Change aleatoirement la couleur de la premiere case et la zone des cases de sa couleur
 *	args: Matrice, nbCases, nombre de couleurs
 */
int strategie_aleatoire_rec(Grille* G, int ** tab, int nbCases, int nbCl);

//Colorie la case (i, j) et stocke dans une pile la liste des cases de la meme couleur environnantes avant de parcourir cette case
//Incremente un compteur du nombre de casses changees
//ARGS: matrice, colonne, ligne, couleur, pointeur vers taille, taille de la matrice
void colorie_zone_imp(int ** tab, int i, int j, int cl, int* taille, int nbCases);

/*	
 *	Change aleatoirement la couleur de la premiere case et la zone des cases de sa couleur
 *	args: Matrice, nbCases, nombre de couleurs
 */
int strategie_aleatoire_imp(Grille* G, int ** tab, int nbCases, int nbCl);

//Strategie aleatoire avec la methode rapide, rend le nombre d'iterations
int strategie_aleatoire_rapide(Grille* G, int ** tab, int nbCases, int nbCl);

#endif
