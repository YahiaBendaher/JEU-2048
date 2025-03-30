#include <cstdlib> // pour srand, exit
#include <time.h>  // pour time
#include <iostream>
#include <vector>

using namespace std;


#ifndef _JEU_2048
#define _JEU_2048 1

typedef struct {
  
    vector<vector<int>> table;	// carre de la bonne dimension
    int cible;
    int proportion;
    int score;
} Grille;


bool init(Grille &g, int dimension, int cible, int proportion);
bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion);
void affiche(const Grille &g);
int gauche(Grille &g), droite(Grille &g), haut(Grille &g), bas(Grille &g);
bool succes(const Grille &g);
int proportion(const Grille &g), dimension(const Grille &g);
int score(const Grille &g), vides(const Grille &g), cible(const Grille &g);
bool ajout(Grille &g);


int nouvelle(const Grille &g), place(const Grille &g);
void resetRand(bool mode);

#endif
