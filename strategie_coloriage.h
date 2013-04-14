#ifndef STRATEGIE_COLORIAGE_H
#define STRATEGIE_COLORIAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Flood-It-1.h"
#include "Graphe_Zones.h"


/*
 * Coloriage de la matrice de maniere imperative
 * La fonction colorie la case (i, j) et stocke dans une pile la liste des cases de la meme couleur avant de parcourir cette case
 * Incremente le compteur du nombre de cases changees (taille)
 * arguments: matrice, colonne, ligne, couleur, pointeur vers taille, taille de la matrice
 */
void colorie_zone_imp(int ** tab, int i, int j, int cl, int* taille, int nbCases);

/*
 * Coloriage de la matrice de maniere recursive
 * La fonction colorie la case (i,j) et la zone environnante
 * Effectue un appel recursif si les cases autour sont de la meme couleur que la case visee
 * Incremente le compteur du nombre de cases changees (taille)
 * arguments: matrice, colonne, ligne, couleur, pointeur vers taille, taille de la matrice
 */
void colorie_zone_rec(int ** tab, int i, int j, int cl, int* taille, int nbCases);

/*
 *  Strategie aleatoire imperative
 *  Change aleatoirement la couleur de la premiere case et la zone des cases de sa couleur
 *  arguments: Matrice, nbCases, nombre de couleurs
 */
int strategie_aleatoire_imp(Grille* G, int ** tab, int nbCases, int nbCl);

/*
 * Strategie aleatoire
 * Change aleatoirement la couleur de la premiere case et la zone des cases de sa
 * arguments: Matrice, nbCases, nombre de couleurs
 */
int strategie_aleatoire_rec(Grille* G, int ** tab, int nbCases, int nbCl);

/*
 * Strategie aleatoire avec la methode rapide
 * Rend le nombre d'iterations
 */
int strategie_aleatoire_rapide(Grille* G, int ** tab, int nbCases, int nbCl);


/*
 *Choix des couleurs qui menent le plus rapidement possible au bord inferieur droit puis 
 * appel de max-bordure
 */
int StrategieLarge(Grille* Grille, int **M, int nbCases);



#endif
