#ifndef FLOODIT1
#define FLOODIT1
//a
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Flood-It-1.h"

int main(int argc,char**argv){

	int nbcase, nbcl, nivdif, graine, i, j, **M, cpt;
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
	if(M==NULL)
	{
		exit(EXIT_FAILURE);
	}

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
	/*
	   int taille = 0, iterStrategie;

	   int coul = M[0][0] == 0? 1 : 0;

	//colorie_zone_rec(M, 0, 0, coul, &taille, nbcase);
	// iterStrategie = strategie_aleatoire_rec(G, M, nbcase, nbcl); //Strategie recursive

	iterStrategie = strategie_aleatoire_imp(G, M, nbcase, nbcl); //Strategie imperative

	printf("%d Iterations necessaires!\n", iterStrategie);

	for (i=0;i<nbcase; i++ )
	{
	for (j=0;j<nbcase;j++){
	Grille_chg_case(G,i,j,M[i][j]);
	}
	}
	*/
	//V=(int **)

	printf("\t\t\t Iterations: %d\n",  strategie_aleatoire_rapide(G, M, nbcase, nbcl));

	/*
	int couleurTest = M[0][0] == 0? 1 : 0;

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

	Zones z; 
	z.nbcase = nbcase; 

	init_Zones(M, &z); 

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	colorieZone(M, &z, couleurTest, &cpt); 
	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	aggranditZone(M, &z, couleurTest);	
	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	//detruitListe(z.B); //--> Boucle infinie
	//z.B = NULL;
	//Apres l'ajoute de z-B = NULL dans aggranditZone, l'erreur est que la fenetre ne peut plus se fermer
	// Erreur de seg a Grille_ferme_fenetre
	//

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	detruitListe(z.Lzsg);
	z.Lzsg = NULL;
	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

	//	for(i = 0; i<nbcase; i++)
	//	{
	//		free(z.App[i]);
	//	}
	*/
	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

	Grille_redessine_Grille();

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	Grille_attente_touche();

	//	while(1);

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	Grille_ferme_fenetre();

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	Grille_free(&G);
	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );


	fprintf(stderr, "%s %d\n\n \t\tFIN DU MAIN!\n\n", __FILE__, __LINE__ );
	return 0;
}


//Colorie la case (i, j) et stocke dans une pile la liste des cases de la meme couleur avant de parcourir cette case
//Incremente un compteur du nombre de casses changees
//ARGS: matrice, colonne, ligne, couleur, pointeur vers taille, taille de la matrice
void colorie_zone_imp(int ** tab, int i, int j, int cl, int* taille, int nbCases)
{
	Pile p; //Pile des cases a modifier
	init_pile(&p);

	Element *e = NULL; //Case actuelle

	int couleurActuelle = tab[i][j]; //Memorisation de la couleur avant changement

	if(cl == couleurActuelle) //Evite les boucles infinies si la case a deja la couleur demandee
	{
		return;
	}

	empile(&p, i , j); //Avant d'entammer la boucle empilement de la premiere case

	while(! pile_vide(p)) //Tant que la pile n'est pas vide
	{

		e = depile(&p); //On recupere une nouvelle case actuelle

		i = e->i; //Memorisation des coordonnes de la couleur actuelle
		j = e-> j;
		//Changement de la couleur de l'element actuel
		tab[i][j] = cl;

		//Verification des couleurs des cases environnantes
		if( (i > 0) && (couleurActuelle == tab[i-1][j])) //A gauche
		{
			fprintf(stderr, "Panning on going to: i->%d j->%d\n", (i - 1), j);
			empile(&p, (i-1), j); //On empile une prochaine case

		}
		if( (j > 0) && (couleurActuelle == tab[i][j-1])) //Au dessus
		{
			fprintf(stderr, "Panning on going to: i->%d j->%d\n", i, (j - 1));
			empile(&p, i, (j - 1)); //On empile une prochaine case
		}
		if( (i < (nbCases - 1)) && (tab[i+1][j] == couleurActuelle)) // A droite
		{
			fprintf(stderr, "Panning on going to: i->%d j->%d\n", (i + 1), j);
			empile(&p, (i+1), j); //On empile une prochaine case
		}
		if( (j < (nbCases - 1)) && (tab[i][j+1] == couleurActuelle)) //En dessous
		{
			fprintf(stderr, "Panning on going to: i->%d j->%d\n", i, (j + 1));
			empile(&p, i, (j+1)); //On empile une prochaine case
		}

		free(e); //liberation de la case actuelle
		(*taille)++;
	}

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
int strategie_aleatoire_imp(Grille* G, int ** tab, int nbCases, int nbCl)
{
	srand(time(NULL)); //Generation de la graine
	int r, i, j, taille = 0, cpt = 0;

	while(taille < ( (nbCases * nbCases) - 1))
	{

		fprintf(stderr, "-------------- Changement de couleur -------------\n");

		taille = 0; //initialisation du compteur 
		r = rand() % nbCl; //Initialisation de la couleur aleatoire € [0;nbCl[
		colorie_zone_imp(tab, 0, 0, r, &taille, nbCases);	

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

//
//Strategie aleatoire avec la methode rapide, rend le nombre d'iterations
int strategie_aleatoire_rapide(Grille* G, int ** tab, int nbCases, int nbCl)
{
	srand(time(NULL)); //Generation de la graine
	int r, i, j, taille = 0, cpt = 0;

	Zones z;
	z.nbcase = nbCases; 
	z.nbcl = nbCl;
	init_Zones(tab, &z); 

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

	while(taille < ((nbCases * nbCases)-4))
	{
		taille = 0; //initialisation du compteur 
		r = rand() % nbCl; //Initialisation de la couleur aleatoire € [0;nbCl[

		if(r == tab[0][0] || z.B[r] == NULL) //Si la ZSG est deja de cette couleur
		  {//Ou qu'aucune case de la bordure ne l'est
			continue; //Evite les iterations inutiles
		}

		colorieZone(tab, &z, r, &taille);	
		fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

		aggranditZone(tab, &z, r);	
		fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

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
		fprintf(stderr, "%s %d %d %d\n", __FILE__, __LINE__, taille, nbCases );
	}

	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );
	//detruitListe(z.B); //--> Boucle infinie
	//z.B = NULL;
	detruitListe(z.Lzsg);
	z.Lzsg = NULL;
	fprintf(stderr, "%s %d\n", __FILE__, __LINE__ );

	return cpt;
}
#endif
