#include <cstdlib> // pour srand, exit
#include <time.h>  // pour time
#include <iostream>
#include <vector>

using namespace std;

/* les lignes 
 * #ifndef  _JEU_2024
 * #define  _JEU_2024 1
 * ...
 * #endif
 * qui encadrent les definitions utiles servent à eviter que le compilateur
 * definisse deux fois les memes identificateurs (ce qui provoquerait une
 * erreur) au cas ou vous feriez deux fois #include "jeu.h"
 * Le compilateur ne traite les lignes que si la macro _JEU_2048 n'est
 * pas definie, ce qu'il s'empresse de faire quand il voit ce code pour la
 * premiere fois.
 */
#ifndef _JEU_2048
#define _JEU_2048 1

typedef struct {
  // structure a completer selon vos besoins.
    vector<vector<int>> table;	// carre de la bonne dimension
    int cible;
    int proportion;
    int score;
} Grille;

/* déclarations de fonctions. Tout fichier qui fait un include de jeu.h
 * connaîtra donc les en-têtes de ces fonctions.
 */
bool init(Grille &g, int dimension, int cible, int proportion);
bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion);
void affiche(const Grille &g);
int gauche(Grille &g), droite(Grille &g), haut(Grille &g), bas(Grille &g);
bool succes(const Grille &g);
int proportion(const Grille &g), dimension(const Grille &g);
int score(const Grille &g), vides(const Grille &g), cible(const Grille &g);
bool ajout(Grille &g);

// pour les éventuelles extensions
void restaure(Grille &g, string filename);
void sauve(const Grille &g, string filename);

// pour les fonctions mises à disposition
int nouvelle(const Grille &g), place(const Grille &g);
void resetRand(bool mode);

#endif
