#include "io.h"
#include "math.h"


/**
  * \fn affiche_cycle (int cycles,int c)
	*	Affiche le nombres de cycle que la grille a vécu.
	*
  * \relatesalso grille
	* \param cycles Le nombre de cycles.
	* \param c Le nombre de colonnes de la grille.
*/
void affiche_cycle (int cycles,int c){
	int i;
	for(i=0;i<2*c-(int)log10(cycles+1)/2;i++)printf(" ");
	printf("%d\n",cycles );
	for(i=0;i<2*c-3;i++)printf(" ");
	printf("cycles");
	return;
}

/**
  * \fn affiche_trait (int c, int* lignes)
	*	Affiche les traits de la grille.
	*
  * \relatesalso grille
	* \param c Le nombre de colonnes.
  * \param lignes les temps de cycles.
*/
void affiche_trait (int c, int* lignes){
	int i;
	for (i=0; i<c; ++i) printf ("|-%d-",lignes[i]>0?lignes[i]:0);
	printf("|\n");
	return;
}

/**
  * \fn affiche_ligne (int c, int* ligne)
	*	Affiche la ligne d'une grille.
	*
  * \relatesalso grille
  * \param c Le nombre de colonnes.
  * \param ligne Le tableau contenant l'état des cellules.
*/

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i){
		if (ligne[i] == 0 ) printf ("|   ");
		else if(ligne[i]==-1) printf("| X ");
		else printf ("| # ");
	}
	printf("|\n");
	return;
}

/**
  * \fn affiche_grille (grille g)
	*	Affiche une grille dans la console à partir des fonctions affiche_ligne
	* et affiche_trait. Les cases vivantes sont indiqué par un O dans la case.
	*
  * \relatesalso grille
  * \param g  La grille de référence pour l'affichage.
*/



void affiche_grille (grille g){
	int i=0, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c,g.cellules[i]);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c, g.cellules[i]);
	}
	printf("\n");
	return;
}

/**
  * \fn efface_grille(grille g)
	*	Reset l'affichage. Cette fonction remplace tous les caractères théoriquement
	* placé précedément par affiche_grille par un espace et replace le curseur
	* au début.
	*
  * \relatesalso grille
  * \param g La grille de référence pour supprimer l'affichage.
*/


void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2+5);
	int i,j;
	for (j=0; j<g.nbl*2+5;j++){
		for (i=0; i<g.nbc; ++i) printf("       ");
		printf("\n" );
	}
	printf("\e[%dA",g.nbl*2+5);

}

void efface_cycle(){
	printf("\eA" );
}

/**
  * \fn void remplacer_grille(grille *g);
  *	Récupère un pointeur d'une grille existante, et la remplacer par une
  * toute nouvellle en demandant à l'utilisateur d'entrer un chemin.
  *
  * \param g La grille à remplacer
  * \warning provoque une erreur et mets en échec le programme si le chemin n'est pas correct.
*/

void remplacer_grille(grille *g){
	int c = getchar();
	int sizeRead = 0;
	int sizeMax = 50;
	char* filename = malloc(sizeof(char)*sizeMax);
	while ((c = getchar()) != '\n' && EOF) {
		filename[sizeRead] = c;
		sizeRead++;
		if(sizeRead>=sizeMax){
			sizeMax+=10;
			filename = realloc(filename,sizeof(char)*sizeMax);
		}
	}
	filename[sizeRead] ='\0';
	init_grille_from_file(filename,g);
	free(filename);
}




void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	long cycles = 0;
	int AGE_STATE = 1;
	int CYCLIQUE = 1;
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc,AGE_STATE,CYCLIQUE);
				efface_grille(*g);
				efface_cycle();
				affiche_cycle(cycles,g->nbc);
				affiche_grille(*g);
				cycles++;
				break;
			}
			case 'n' :
			{ // touche "n" pour changer de grille
				efface_grille(*g);
				efface_cycle();
				remplacer_grille(g);
				alloue_grille(g->nbl,g->nbc,gc);
				copie_grille(*g,*gc);
				cycles = 0;
				affiche_cycle(cycles,g->nbc);
				affiche_grille(*g);
				break;
			}
			case 'v':
				AGE_STATE = (AGE_STATE>0)?0:1;
				break;
			case 'c':
				CYCLIQUE = (CYCLIQUE>0)?0:1;
				break;
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}
