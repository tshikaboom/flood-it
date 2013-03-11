#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Flood-It-1.h"

int main(int argc,char**argv){

	int nbcase, nbcl, nivdif, graine, i, j, **M;
	Grille *G;
	clock_t temps_initial, /* Temps initial en micro-secondes */ temps_final;   /* Temps final en micro-secondes */
	float temps_cpu;     /* Temps total en secondes */ 

	if(argc!=5)
	{
		printf("usage: %s <nb_de_case nb_de_couleurs niveau_difficulte graine>\n",argv[0]);
		return 1;
	}

	//Recuperation des arguments
	sscanf(argv[1], "%d", &nbcase);
	sscanf(argv[2], "%d", &nbcl);
	sscanf(argv[3], "%d", &nivdif);
	sscanf(argv[4], "%d", &graine);

	/* Generation de l'instance */

	M=(int **) malloc(sizeof(int*)*nbcase);

	for (i=0;i<nbcase;i++)
	{
		M[i]=(int*) malloc(sizeof(int)*nbcase);
		if (M[i]==0) printf("OUCH\n");
	}

	Gene_instance_genere_matrice(nbcase, nbcl, nivdif, graine, M);

	/* Affichage de la grille */

	Grille_init(nbcase,nbcl, 500,&G);

	Grille_ouvre_fenetre(G);

	for (i=0;i<nbcase; i++ )
	{
		for (j=0;j<nbcase;j++){
			Grille_chg_case(G,i,j,M[i][j]);
		}
	}
	Grille_redessine_Grille();

	Grille_attente_touche();

	int taille = 0, iterStrategie;

	int coul = M[0][0] == 0? 1 : 0;

	//colorie_zone_rec(M, 0, 0, coul, &taille, nbcase);
	iterStrategie = strategie_aleatoire_rec(G, M, nbcase, nbcl);

	printf("%d Iterations necessaires!\n", iterStrategie);


	for (i=0;i<nbcase; i++ )
	{
		for (j=0;j<nbcase;j++){
			Grille_chg_case(G,i,j,M[i][j]);
		}
	}

	Grille_redessine_Grille();

	Grille_attente_touche();

	//	while(1);

	Grille_ferme_fenetre();

	Grille_free(&G);


	return 0;
}

//Colorie la case (i,j) et la zone environnante, appel recursif si les cases autour sont de la meme couleur que la case visee
//Incremente un compteur du nombre de casses changees
//ARGS: matrice, colonne, ligne, couleur, pointeur vers taille, taille de la matrice
void colorie_zone_rec(int ** tab, int i, int j, int cl, int* taille, int nbCases)
{
	int couleurActuelle = tab[i][j]; //Memorisation de la couleur avant changement

	//Changement de la couleur avant l'appel recursif pour eviter les boucles infinies

	tab[i][j] = cl;
	
	if(cl == couleurActuelle) //Evite les boucles infinies si la case a deja la couleur demandee
	{
		return;
	}

	//Verification des couleurs des cases environnantes
	if( (i > 0) && (couleurActuelle == tab[i-1][j])) //A gauche
	{
		fprintf(stderr, "Going to: i->%d j->%d\n", (i - 1), j);
		colorie_zone_rec(tab, (i-1), j, cl, taille, nbCases);
	}

	if( (j > 0) && (couleurActuelle == tab[i][j-1])) //Au dessus
	{
		fprintf(stderr, "Going to: i->%d j->%d\n", i, (j - 1));
		colorie_zone_rec(tab, i, (j-1), cl, taille, nbCases);
	}
	if( (i < (nbCases - 1)) && (tab[i+1][j] == couleurActuelle)) // A droite
	{
		fprintf(stderr, "Going to: i->%d j->%d\n", (i + 1), j);
		colorie_zone_rec(tab, (i+1), j, cl, taille, nbCases);
	}

	if( (j < (nbCases - 1)) && (tab[i][j+1] == couleurActuelle)) //En dessous
	{
		fprintf(stderr, "Going to: i->%d j->%d\n", i, (j + 1));
		colorie_zone_rec(tab, i, (j+1), cl, taille, nbCases);
	}


	(*taille)++;
}

/*	
 *	Change aleatoirement la couleur de la premiere case et la zone des cases de sa couleur
 *	args: Matrice, nbCases, nombre de couleurs
 */
int strategie_aleatoire_rec(Grille* G, int ** tab, int nbCases, int nbCl)
{
	srand(time(NULL)); //Generation de la graine
	int r, i, j, taille = 0, cpt = 0;

	while(taille < (nbCases * nbCases))
	{
		taille = 0; //initialisation du compteur 
		r = rand() % nbCl; //Initialisation de la couleur aleatoire € [0;nbCl[
		colorie_zone_rec(tab, 0, 0, r, &taille, nbCases);	

		for (i=0;i<nbCases; i++ )
		{
			for (j=0;j<nbCases;j++)
			{
				Grille_chg_case(G,i,j,tab[i][j]);
			}
		}
		Grille_redessine_Grille();

		Grille_attente_touche();

		cpt++;
	}

	return cpt;
}
