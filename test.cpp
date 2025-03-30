#include "jeu.h"
#include <cassert>

/* A faire dans un second temps: petit menu pour exécuter les commandes de
 * l'utilisateur
 */

int interactif() {
    bool continuerJeu = true;  // Variable pour continuer ou arrêter le jeu selon le choix de l'utilisateur.
    do{ 
    // Message d'accueil et instructions pour l'utilisateur.
    cout << endl << "Bienvenue dans le jeu 2048 !" << endl;
    cout << "Utilisez les touches 'h' (haut), 'b' (bas), 'g' (gauche), 'd' (droite) pour déplacer les tuiles." << endl;

    // Création et initialisation de la grille de jeu.
    Grille g;
    unsigned int adresseGrille = (uintptr_t)&g;
    int proportionAleatoire = adresseGrille % 10;
    int taille, objectif;
    cout << "Entrez la taille de la grille (4 minimum) : ";
    cin >> taille;
    cout << "Définissez l'objectif à atteindre (ex: 2048) : ";
    cin >> objectif;
    assert(init(g, taille, objectif, proportionAleatoire));

    // Affichage initial de la grille.
    affiche(g);
    cout << "Objectif : atteindre " << g.cible << "." << endl << endl;

    // Boucle principale du jeu pour gérer les mouvements.
    bool finDeJeu = false;
    bool aGagne = false;
    while (!aGagne and !finDeJeu) {
        char mouvement;
        cout << "Votre mouvement ('h', 'b', 'g', 'd') : ";
        cin >> mouvement;

        // Gestion des entrées de l'utilisateur pour les mouvements.
        if (mouvement == 'h' and haut(g) != -1) {
            ajout(g);
        } else if (mouvement == 'b' and bas(g) != -1) {
            ajout(g);
        } else if (mouvement == 'g' and gauche(g) != -1) {
            ajout(g);
        } else if (mouvement == 'd' and droite(g) != -1) {
            ajout(g);
        } else {
            cout << "Veuillez saisir une instruction valide." << endl;
            continue;  // Demande de saisie valide si la commande n'est pas reconnue.
        }

        // Réaffichage de la grille après chaque mouvement.
        affiche(g);
        // Vérification de la condition de victoire.
        aGagne = succes(g);

        // Tester si d'autres mouvements sont possibles en créant une copie de la grille.
        Grille testG = g;
        finDeJeu = (gauche(testG) == -1) and (droite(testG) == -1) and
                   (haut(testG) == -1) and (bas(testG) == -1);
    }

    // Afficher le résultat du jeu.
    if (finDeJeu) {
        cout << "Aucun mouvement possible, vous avez perdu." << endl;
    } else if (aGagne) {
        cout << "Bravo ! Vous avez atteint l'objectif !" << endl;
    }

    // Demande de nouvelle partie.
    char reponseUtilisateur;
    cout << "Souhaitez-vous jouer à nouveau (o/n) ? ";
    cin >> reponseUtilisateur;
    continuerJeu = (reponseUtilisateur == 'o' );
    }while (continuerJeu);

    return 0;  // Terminer la fonction.
}

/* Quelques fonctions de test mises à disposition.
 * Elles sont lancées par la fonction testFV qui est elle-même lançable
 * dans la fonction main()à située en fin de fichier.
 * Pour l'instant l'appel à cette fonction est mis en commentaire.
 */


void teste3() {
  Grille g;
  vector<vector<int>> v =
    { { 8, 4, 4, 4 }, { 4, 0, 4, 4 }, { 4, 4, 4, 4 }, { 4, 0, 0, 4} };
  cout << "Debut du test3\n";
  assert(charge(g, v, 32, 7)); // charge et teste le resultat
  affiche(g);

  gauche(g); affiche(g);
  droite(g); affiche(g);
  haut(g);   affiche(g);
  gauche(g); affiche(g);
  haut(g);   affiche(g);
  bas(g);    affiche(g);
  assert(score(g) == 128 and succes(g));
  cout << "Teste3 OK" << endl;
}

void teste3bis() {
  Grille g;
  vector<vector<int>> v =
    { { 2, 4, 0, 0, 4 }, { 4, 0, 4, 8, 8 }, { 0, 0, 4, 0, 4 }, { 2, 4, 0, 0, 4},
      { 2, 4, 0, 4, 2 }
    };
  cout << "Debut du teste3bis" << endl;
  assert(charge(g, v, 64, 10)); // avec que des tuiles de valeur 2
  affiche(g);
  
  gauche(g); affiche(g);
  assert(score(g) == 56 and gauche(g) == -1);
  cout << "teste3bis-I: OK" << endl;
  // On repart de la meme configuration initiale mais on essaye
  // un autre deplacement
  Grille g2;
  assert(charge(g2, v, 8, 0));
  affiche(g2);
  
  haut(g2);   affiche(g2);
  bas(g2);    affiche(g2);
  droite(g2); affiche(g2);
  assert(score(g2) == 68 and vides(g2) == 16);
  cout << "teste3bis-II: OK" << endl;
  cout << "Fin de teste3bis" << endl;
}

void teste4() {
  Grille g;
  vector<vector<int>> v =
  // une grille bloquée.
    { { 128, 8, 2, 4 }, { 4, 16, 4, 8 }, { 8, 2, 8, 4}, { 2, 4, 16, 32} };
  cout << "Debut du test4" << endl;
  assert(charge(g, v, 2048, 7));
  affiche(g);
  
  assert(gauche(g) == -1 and droite(g) == -1 and
	 haut(g)   == -1 and droite(g) == -1);
  affiche(g);
  cout << "Teste4 OK" << endl;
}

void teste5() {
  Grille g;
  cout << "Debut du test5" << endl;
  assert(init(g, 5, 8, 0)); // on ne cree que des tuiles de valeur 4
  affiche(g);
  
  haut(g);   affiche(g);
  droite(g); affiche(g);
  assert(score(g) == 8 and succes(g));
  cout << "Teste5 OK" << endl;
}



void testFV() {
  teste3();
  teste3bis();
  teste4();
  teste5();
}

int main() {
  testFV();
  interactif();
  return 0;
}
