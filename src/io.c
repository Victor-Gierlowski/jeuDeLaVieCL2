#include "io.h"


/**
  * \fn affiche_trait (int c)
	*
	*	Affiche les traits de la grille.
	*
  * \relatesalso grille
  * \relatesalso affiche_ligne
  * \relatesalso affiche_grille
  * \param c int, Le nombre de colonnes.
*/
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
  * \fn affiche_ligne (int c, int* ligne)
	*
	*	Affiche la ligne d'une grille.
	*
  * \relatesalso grille
  * \relatesalso affiche_trait
  * \relatesalso affiche_grille
  * \param c int, Le nombre de colonnes.
  * \param lignes int*, Le tableau contenant l'état des cellules.
*/

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

/**
  * \fn affiche_grille (grille g)
	*
	*	Affiche une grille dans la console à partir des fonctions affiche_ligne
	* et affiche_trait. Les cases vivantes sont indiqué par un O dans la case.
	*
  * \relatesalso grille
  * \relatesalso efface_grille
  * \param g grille, La grille de référence pour l'affichage.
*/

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

/**
  * \fn efface_grille(grille g)
	*
	*	Reset l'affichage. Cette fonction remplace tous les caractères théoriquement
	* placé précedément par affiche_grille par un espace et replace le curseur
	* au début.
	*
  * \relatesalso grille
  * \relatesalso affiche_grille
  * \param g grille, La grille de référence pour supprimer l'affichage.
*/


void efface_grille (grille g){
<<<<<<< HEAD
	printf("\n\e[%dA",g.nbl*2 + 4);
=======
	printf("\n\e[%dA",g.nbl*2 + 5);
>>>>>>> f25eeb3416a039318873a201a6e49a84db6a1cea
	int i,j;
	for (j=0; j<g.nbl*2+4;j++){
		for (i=0; i<g.nbc; ++i) printf("       ");
		printf("\n" );
	}
<<<<<<< HEAD
	printf("\e[%dA",g.nbl*2 + 5);

}

/**
  * \fn void remplacer_grille(grille *g);
  *	Récupère un pointeur d'une grille existante, et la remplacer par une
  * toute nouvellle en demandant à l'utilisateur d'entrer un chemin.
  *
  * \param g grille, La grille à remplacer
  * \warning provoque une erreur et mets en échec le programme si le chemin n'est pas correct.
*/

void remplacer_grille(grille *g){
	int c = getchar();
	// while (c= getchar()!='\n' && c != EOF) {printf("%c",c);}
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
=======
	printf("\n\e[%dA",g.nbl*2 + 4);

}

void nouvelle_grille(grille *g){
	int sizeRead = 0;
	int sizeMax = 50;
	int c = getchar();
	char* filename = malloc(sizeof(char)*sizeMax);
	scanf("%s", filename);
	printf("%s\n", &filename);
	// while (c = getchar() != '\n' && c != EOF) {
	// 	filename[sizeRead] = c;
	// 	sizeRead++;
	// 	if(sizeRead >= sizeMax){
	// 		sizeMax+=1;
	// 		filename = realloc(filename,sizeof(char)*sizeMax);
	// 	}
	// }
	// filename = realloc(filename,sizeof(char)*sizeRead);
	// filename[sizeRead+1] = '\0';
>>>>>>> f25eeb3416a039318873a201a6e49a84db6a1cea
	init_grille_from_file(filename,g);
	free(filename);
}




void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
<<<<<<< HEAD
			{ // touche "n" pour changer de grille
				efface_grille(*g);
				remplacer_grille(g);
=======
			{
				efface_grille(*g);
				nouvelle_grille(g);
>>>>>>> f25eeb3416a039318873a201a6e49a84db6a1cea
				affiche_grille(*g);
				break;
			}
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
