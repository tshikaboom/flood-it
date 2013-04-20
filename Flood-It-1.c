#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strategie_coloriage.h"
#include "Flood-It-1.h"

int main(int argc,char**argv)
{
  int nbcase, nbcl, nivdif, graine, i, j;
  int **M;
  Grille *G;
  //  clock_t
  //    temps_initial, // Temps initial en micro-secondes
  //    temps_final;   // Temps final en micro-secondes 
  //  float temps_cpu; // Temps total en secondes

  if (argc != 5) {
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
      exit(EXIT_FAILURE);

  for (i=0;i<nbcase;i++) {
      M[i]=(int*) malloc(sizeof(int)*nbcase);
      if (M[i]==0) printf("OUCH\n");
    }

  Gene_instance_genere_matrice(nbcase, nbcl, nivdif, graine, M);


  /* Affichage de la grille */
  Grille_init(nbcase,nbcl, 500,&G);
  Grille_ouvre_fenetre(G);
  for (i=0;i<nbcase; i++ )
    for (j=0;j<nbcase;j++)
      Grille_chg_case(G,i,j,M[i][j]);

  Grille_redessine_Grille();
  //  Grille_attente_touche();

  int menuchoix;
  
  do {
    printf("Flood-it: menu\n");
    printf("1 Strategie recursive\n");
    printf("2 Strategie iterative\n");
    printf("3 Strategie rapide\n");
    printf("4 Strategie max-bordures\n");
    printf("5 Strategie largeur\n\n");
    printf("0 Quitter\n");
    printf(">> ");
    
    scanf("%d", &menuchoix);

    switch (menuchoix) {
    case 1:
      Gene_instance_genere_matrice(nbcase, nbcl, nivdif, graine, M);
      Grille_init(nbcase,nbcl, 500,&G);
      
      Grille_ouvre_fenetre(G);
      for (i=0;i<nbcase; i++ )
	for (j=0;j<nbcase;j++)
	  Grille_chg_case(G,i,j,M[i][j]);

      printf("%d iterations au total\n",  strategie_aleatoire_rec(G, M, nbcase, nbcl));
      Grille_redessine_Grille();
      Grille_attente_touche();
      Grille_ferme_fenetre();

      Grille_free(&G);
      break;
    case 2:
            Gene_instance_genere_matrice(nbcase, nbcl, nivdif, graine, M);
      Grille_init(nbcase,nbcl, 500,&G);
      
      Grille_ouvre_fenetre(G);
      for (i=0;i<nbcase; i++ )
	for (j=0;j<nbcase;j++)
	  Grille_chg_case(G,i,j,M[i][j]);
      printf("%d iterations au total\n",  strategie_aleatoire_imp(G, M, nbcase, nbcl));
      Grille_redessine_Grille();
      Grille_attente_touche();
      Grille_ferme_fenetre();

      Grille_free(&G);
      break;
    case 3:
      Gene_instance_genere_matrice(nbcase, nbcl, nivdif, graine, M);
      Grille_init(nbcase,nbcl, 500,&G);
      
      Grille_ouvre_fenetre(G);
      for (i=0;i<nbcase; i++ )
	for (j=0;j<nbcase;j++)
	  Grille_chg_case(G,i,j,M[i][j]);
      printf("%d iterations au total\n",  strategie_aleatoire_rapide(G, M, nbcase, nbcl));
      Grille_redessine_Grille();
      Grille_attente_touche();
      Grille_ferme_fenetre();

      Grille_free(&G);
      break;
    case 4: 
      Gene_instance_genere_matrice(nbcase, nbcl, nivdif, graine, M);
      Grille_init(nbcase,nbcl, 500,&G);

      Grille_ouvre_fenetre(G);
      for (i=0;i<nbcase; i++ )
	      for (j=0;j<nbcase;j++)
		      Grille_chg_case(G,i,j,M[i][j]);
      printf("%d iterations au total\n",  maxBordure(G, M, nbcase));
      Grille_redessine_Grille();
      Grille_attente_touche();
      Grille_ferme_fenetre();

      Grille_free(&G);

      break;
    case 5:
      Gene_instance_genere_matrice(nbcase, nbcl, nivdif, graine, M);
      Grille_init(nbcase,nbcl, 500,&G);

      Grille_ouvre_fenetre(G);
      for (i=0;i<nbcase; i++ )
	      for (j=0;j<nbcase;j++)
		      Grille_chg_case(G,i,j,M[i][j]);
      printf("%d iterations au total\n",  StrategieLarge(G, M, nbcase));
      Grille_redessine_Grille();
      Grille_attente_touche();
      Grille_ferme_fenetre();

      Grille_free(&G);
    case 0:
      break;
    default:
      printf("choix?\n\n");
    }
  } while (menuchoix < 0 || menuchoix > 4 || menuchoix != 0);
 

  //  Grille_redessine_Grille();
  //  Grille_attente_touche();

  //	while(1);

  //  Grille_ferme_fenetre();

  //  Grille_free(&G);
  return 0;
}

