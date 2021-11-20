#include "grille.h"


/**
  * \fn alloue_grille(int l, int c,grille* g)
	*
	*
	* Créer une grille, en lui allouant la mémoire nécessaire au bi-dimensionnelle.
	* Définie aussi les attributs de lignes et colonnes selons les paramètres
  * \relatesalso grille
  * \param l int, nombre de lignes de la grille
  * \param c int, nombre de colonnes de la grille
  * \param g grille, le pointeur de la grille à qui allouer la mémoire
*/


void alloue_grille (int l, int c, grille* g){
	g->nbl = l;
	g->nbc = c;
	int i;
	g->cellules = malloc(sizeof(int*)*c);
	for(i=0;i<c;i++){
		g->cellules[i] = calloc(l,sizeof(int**));
	}
}

/**
  * \fn libere_grille(grille* g)
	* Libère toute la mémoire alloué au tableau de la grille, ainsi que le pointeur de la grille.
  * \relatesalso grille
  * \param g grille, la grille dont la mémoire doit être libéré
*/

void libere_grille (grille* g){
	int i =0;
	for(i=0;i<g->nbc;i++){
		free(g->cellules[i]);
	}
	free(g->cellules);
	free(g);
}


/**
  * \fn init_grille_from_file(char * filename, grille* g)
	*	Lit le fichier passé en paramètre pour créer une grille et la stocker dans le pointeur grille transmit.
	*
	* \relatesalso grille
  * \param filename char*, Le chemin du fichier contenant les informations de la grille.
  * \param g grille*, le pointeur de la grille à qui associé les données.
*/


void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);


	int i,j,n,l,c,vivantes=0,non_viable=0;

	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	alloue_grille(l,c,g);

	// Récupère les cellules vivantes
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	//Récupère les cellules non viables.
	fscanf(pfile, "%d", & non_viable);
	for (n=0; n< non_viable; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}


	fclose (pfile);
	return;
}
/**
  * \fn  copie_grille (grille gs, grille gd)
	*	Permet la duplication des valeurs d'une grille sans partager les cases mémoires.
	*
	* \relatesalso grille
  * \param gs grille initial, Grille de référence.
  * \param gd grille copie, Celle qui va prendre les valeurs.
*/

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;
}
