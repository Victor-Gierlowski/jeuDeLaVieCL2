#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
void affiche_grille (grille g);

// effacement d'une grille
void efface_grille (grille g);

<<<<<<< HEAD
// Récupère une grille par l'utilisateur et remplace celle en argument
void remplacer_grille(grille *g);
=======
// Récupère une grille par l'utilisateur
void nouvelle_grille(grille *g);
>>>>>>> f25eeb3416a039318873a201a6e49a84db6a1cea

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
