#include "jeu.h"

int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v;
}
int compte_voisins_vivants_NON_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	//Compteurs pour matrice 3x3
	int i1,i2;
	for(i1=-1;i1<2;i1++){
		for (i2 = -1; i2 < 2; i2++) {
			// On vérifie qu'on reste dans les cases définie de la grille
			// Et que ce n'est pas la case centrale
			if(i1 + i <l&& i1+i>=0 && i2+j < c&& i2+j >=0 && !(i1==0 && i2==0)){
				printf("%d %d\n",i1+i,i2+j );
				v+=est_vivante(i1+i,i2+j,g);
			}
		}
	}
	// v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	// v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	// v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	// v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	// v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	// v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	// v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	// v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	return v;
}

void evolue (grille *g, grille *gc,int AGE_STATE,int CYCLIQUE){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int (*compte_voisins_vivants)(int, int, grille);
	if(CYCLIQUE)
		compte_voisins_vivants=&compte_voisins_vivants_cyclique;
	else
		compte_voisins_vivants=&compte_voisins_vivants_NON_cyclique;
	int i,j,l=g->nbl, c = g->nbc,v;
	int age;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			age =(AGE_STATE >0)?est_jeune(i,j,*gc):1;

			v = (*compte_voisins_vivants)(i, j, *gc);
			if (est_vivante(i,j,*g) & age)
			{ // evolution d'une cellule vivante
				if(AGE_STATE)
					vieillie(i,j,*g);
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else if(!est_jeune(i,j,*g))
				set_morte(i,j,*g);
			else
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
