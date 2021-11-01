#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

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

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5);
	int i,j;
	for (j=0; j<g.nbl*2+4;j++){
		for (i=0; i<g.nbc; ++i) printf("       ");
		printf("\n" );
	}
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
			{
				efface_grille(*g);
				nouvelle_grille(g);
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
