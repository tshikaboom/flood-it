#ifndef ZONESH
#define ZONESH

#include "Pile_case.h"

typedef struct {
	/* Liste des cases de la zone Zsg */
	Liste_case * Lzsg ;
	/* Tableau de listes de cases de la bordure*/
	Liste_case ** B ;
	/* Tableau a double entree des appartenances */
	int ** App ;
	/* nombre de cases */
	int nbcase ;
	/* nombre de couleurs */
	int nbcl ;
} Zones ;


//Renvoie une nouvelle Zone et teste le succes des allocations
void init_Zones(int ** M, Zones *z);

//Ajoute une element a la liste des Zsg et modifide App
void ajoute_Zsg(Zones *z, int i, int j);
//Ajoute un element a la bordure et change sa reference dans App avec cl
void ajoute_Bordure(Zones *z, int i, int j, int clCase);

//Renvoie vrai si la case appartient a la Bordure
int appartient_Bordure_coord(Zones* z, int i, int j);
//Renvoie vrai si la case appartient a la Zsg
int appartient_Zsg(Zones *z, int i, int j);
//Renvoie vrai si la couleur est presente dans la bordure
int appartient_Bordure(int ** M, Zones *z, int cl);

void colorieZone (int **M, Zones *Z, int cl, int *cpt);
void aggranditZone(int ** M, Zones *z, int cl);

#endif
