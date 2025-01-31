#include "jeu.h"


/**
  * \fn  compte_voisins_vivants_cyclique (int i, int j, grille g)
	*	Compte les voisins vivant d'une cellule de manière cyclique.
	* Ressemble à compte_voisins_vivants_NON_cyclique(int i, int j, grille g)
	*
	* \relatesalso grille
  * \param i int ,position Y de la cellule.
	* \param j int ,position X de la cellule.
  * \param g grille copie, Celle qui va prendre les valeurs.
	* \return int v, le nombre de voisins vivants
*/

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

/**
  * \fn  compte_voisins_vivants_NON_cyclique (int i, int j, grille g)
	*	Compte les voisins vivant d'une cellule mais n'est pas cyclique.
	* Ressemble à compte_voisins_vivants_cyclique(int i, int j, grille g)
	*
	* \relatesalso grille
  * \param i int ,position Y de la cellule.
	* \param j int ,position X de la cellule.
  * \param g grille copie, Celle qui va prendre les valeurs.
	* \return int v, le nombre de voisins vivants
*/
int compte_voisins_vivants_NON_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	//Compteurs pour matrice 3x3
	int i1,i2;
	for(i1=-1;i1<2;i1++){
		for (i2 = -1; i2 < 2; i2++) {
			// On vérifie qu'on reste dans les cases définie de la grille
			// Et que ce n'est pas la case centrale
			if(i1 + i <l&& i1+i>=0 && i2+j < c&& i2+j >=0 && !(i1==0 && i2==0)){
				v+=est_vivante(i1+i,i2+j,g);
			}
		}
	}
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
				if ( v==3 && est_viable(i,j,*g)) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
