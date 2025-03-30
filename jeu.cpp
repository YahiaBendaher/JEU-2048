#include "jeu.h"
#include <iomanip> // pour setw dans affichage.
#include <fstream> // pour lecture et écriture dans des fichiers (fonctions sauve et restaure)


/* Les definitions actuelles des fonctions servent uniquement à ce que le
 * compilateur ne râle pas. Il faut bien sur écrire le code de ces fonctions
 */

int vides(const Grille &g) {
    int totalVides = 0;
    
    // On examine chaque ligne dans la grille
    for (size_t i = 0; i < g.table.size(); i=i+1) {
        // On parcoure chaque élément de la ligne
        for (size_t j = 0; j < g.table.at(i).size(); j=j+1) {
            // On vérifie si la cellule est à zéro (donc vide), si oui on augmente le compteur
            if (g.table.at(i).at(j) == 0) {
                totalVides++;
            }
        }
    }
    return totalVides;
}

int proportion(const Grille &g) { return g.proportion; }

int cible(const Grille &g)  { return g.cible; }

int dimension(const Grille &g)  { return g.table.size(); }

int score(const Grille &g)  { return g.score;}

bool succes(const Grille &g) {
    // On suppose initialement qu'aucune case ne remplit la condition
    bool echec = true; // On commence en supposant un échec

    // On Parcour toutes les cases de la grille
    for (int i = 0; i < g.table.size(); i++) {
        for (int j = 0; j < g.table.at(i).size(); j++) {
            // Si une valeur a atteint ou a dépassé la cible, cela signifie que c'est un succès
            if (g.table.at(i).at(j) >= g.cible) {
                echec = false; // Un succès est donc trouvé, donc ce n'est plus un échec
                break; // On sort donc de la boucle dès qu'on a trouvé un succes
            }
        }
        if (!echec) { // si il n'y a pas d'echec
                break; // On sort de la boucle externe 
        }
    }
    return !echec; // Retourner l'inverse de l'échec, c'est-à-dire `true` si succès et false 'sinon'
}

bool ajout(Grille &g){
    // On Commence par compter le nombre de cases vides dans la grille.
    int casesVides = vides(g);
    // Si il n'y a pas de cases vides, il n'est pas possible d'ajouter une nouvelle tuile.
    if (casesVides == 0) {
        // Aucune case vide n'est disponible, donc il est impossible d'ajouter une tuile.
        return false;
    }

    // On génère la valeur de la nouvelle tuile et déterminer la position où elle doit être placée.
    int valeurTuile = nouvelle(g); // Cette fonction suppose de générer un numéro pour la nouvelle tuile.
    int positionTuile = place(g);  // Cette fonction détermine où placer la tuile sur la grille.

    // Si la position calculée pour la nouvelle tuile est plus grande que le nombre de cases vides,
    // alors la position est donc invalide (c'est probablement une erreur de calcul ou de logique).
    if (positionTuile > casesVides) {
        // l'ajout de la tuile a échoué.
        return false;
    }

    // On parcour maintenant la grille pour bien placer la tuile.
    int compteur = 0;  // Compteur pour suivre le nombre de cases vides parcourues.
    for (int i = 0; i < g.table.size(); i=i+1) {
        for (int j = 0; j < g.table.at(i).size();j=j+1) {
            if (g.table.at(i).at(j) == 0) { // Vérifie si la case actuelle est vide.
                compteur++; // Incrémente le compteur pour chaque case vide trouvée.
                if (compteur != positionTuile) {
                    // Si le compteur n'a pas encore atteint la position désignée, on continue la recherche.
                    continue;
                }
                // Si nous avons atteint la position désignée, on place la tuile.
                g.table.at(i).at(j) = valeurTuile;
                return true; // La tuile a été placée avec succès, retourne 'true'.
            }
        }
    }

    // En théorie, nous ne devrions jamais atteindre cette ligne car la tuile devrait être ajoutée ou une erreur doit être signalée plus haut.
    return false;
}

bool init(Grille &g, int dimension, int cible, int proportion) {
    // On Vérifie si 'cible' est une puissance de deux.
    // Une puissance de deux en binaire a un seul bit à '1' et tous les autres à '0'.
    // On divise alors la valeur par deux jusqu'à ce qu'elle devienne 1, en vérifiant si elle est toujours divisible par 2.
    int testCible = cible;
    while (testCible > 1) {
        if (testCible % 2 != 0) {
            // Si le nombre n'est pas divisible par 2 à n'importe quelle étape, ce n'est pas une puissance de deux.
            return false; 
        }
        testCible = testCible / 2; // On continue de diviser par 2 tant qu'on ne trouve pas de contre-exemple.
    }

    // On vérifie les conditions de validité pour les autres paramètres de la grille.
    // 'proportion' doit être entre 0 et 10 strictement, 'cible' doit être plus grande ou égale à  4, et 'dimension' doit être au moins 4.
    if (proportion < 0 or proportion > 10 or cible <= 4 or dimension < 4) {
        return false; // Si une de ces conditions n'est pas respectée, on retourne false.
    }
    
    // On crée une nouvelle table vide de la même dimension donnée 
    // On initialise toutes les cases  à 0, c.à.d qu'elles sont vides.
    vector<vector<int>> nouvelleTable;
    for (int i = 0; i < dimension; i++) {
        vector<int> ligne; // On Crée une nouvelle ligne
        for (int j = 0; j < dimension; j++) {
            ligne.push_back(0); // On Remplit la ligne avec des zéros
        }
        nouvelleTable.push_back(ligne); // On Ajoute la ligne complétée à la grille
    }
    g.table = nouvelleTable;
    g.cible = cible;
    g.proportion = proportion;
    g.score = 0; // Initialisation du score à 0.
    
    // Placement initial de deux tuiles. 
    // Cela permet de démarrer le jeu avec deux tuiles aléatoires sur la grille.
    bool ajoutTuilesReussi = true;
    for (int i = 0; i < 2; i++) {
        if (!ajout(g)) {
            // Si l'ajout d'une tuile échoue, on définit 'ajoutTuilesReussi' à faux et on arrête la boucle.
            ajoutTuilesReussi = false;
            break;
        }
    }

    return ajoutTuilesReussi; // Retourne le succès ou l'échec de l'initialisation de la grille.
}


bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion) {
    // Quelques vérifications pour voir la grille sera valide
    // voir la fonction init() plus haut pour plus de détails
    if (v.size() < 4) {
        cerr << "Nombre de lignes insuffisant: " << v.size() << endl;
        return false;
    }
    g.table = v;
    g.cible = cible;
    g.proportion = proportion;
    g.score=0;
    return true;
}


int droite(Grille &g) {
    bool mouvement = false;  // avec cette nouvelle variable on vérifie si au moins un déplacement ou une fusion de tuiles a eu lieu.

    // On va parcourir chaque ligne de la grille, de droite à gauche.
    for (int i = 0; i < g.table.size(); i=i+1) {
        // D'abord, on doit compresser toutes les tuiles vers la droite.
        // positionCible va nous indiquer où la prochaine tuile non nulle doit aller.
        int positionCible = g.table.size() - 1;
        for (int j = g.table.size() - 1; j >= 0; j=j-1) {
            // On Vérifie si la case courante n'est pas vide.
            if (g.table.at(i).at(j) != 0) {
                // Déplacer la tuile vers positionCible.
                g.table.at(i).at(positionCible) = g.table.at(i).at(j);
                // Si la tuile est déplacée à une nouvelle position, nettoyer l'ancien emplacement.
                if (positionCible != j) {
                    g.table.at(i).at(j) = 0;
                    mouvement = true; // on a eu un mouvement
                }
                positionCible= positionCible - 1;
            }
        }

        // Ensuite, on fusionne les tuiles consécutives identiques, de droite à gauche.
        for (int j = g.table.size() - 1; j > 0; j=j-1) {
            // Si deux tuiles adjacentes sont identiques et non nulles, on les fusionne.
            if (g.table.at(i).at(j) != 0 and g.table.at(i).at(j) == g.table.at(i).at(j - 1)) {
                g.table.at(i).at(j) *= 2;  // On Double la valeur de la tuile.
                g.score += g.table.at(i).at(j);  // On Ajoute la valeur de la tuile fusionnée au score total.
                g.table.at(i).at(j - 1) = 0;  // On Efface la tuile fusionnée.
                mouvement = true;
                j=j-1;  // Passer la tuile suivante qui vient d'être fusionnée pour éviter les fusions multiples.
            }
        }
    }

    // Après avoir traité toutes les lignes, on vérifie si des mouvements ou des fusions ont été réalisés.
    // On Retourne le nombre de cases vides si des changements ont été effectués; sinon, on retourne -1.
    if (mouvement) {
        return vides(g);  // On Calcule et retourne le nombre de cases vides dans la grille.
    } else {
        return -1;  // Aucun mouvement n'a été fait, donc on retourne -1.
    }
}


int gauche(Grille &g) {
    bool mouvement = false;  // Cette variable indique si un déplacement ou une fusion de tuiles a eu lieu.

    // On Parcoure chaque ligne de la grille, de gauche à droite.
    for (int i = 0; i < g.table.size(); i=i+1) {
        // On Examine chaque cellule de la ligne, à l'exception de la dernière.
        for (int j = 0; j < g.table.at(i).size() - 1; j=j+1) {
            if (g.table.at(i).at(j) == 0) continue;  // On Ignore les cases vides.

            // On Trouve la prochaine case non vide à droite.
            int k =1;
            for (k=1 ; j + k < g.table.at(i).size() and g.table.at(i).at(j + k) == 0; k=k+1);

            // On Vérifie si la case actuelle peut fusionner avec cette case non vide trouvée.
            if (j + k < g.table.at(i).size() and g.table.at(i).at(j) == g.table.at(i).at(j + k)) {
                mouvement = true;
                g.table.at(i).at(j) *= 2;  // On Fusionne les tuiles en doublant la valeur de la tuile actuelle.
                g.score += g.table.at(i).at(j);  //On Met à jour le score avec la nouvelle valeur de la tuile fusionnée.
                g.table.at(i).at(j + k) = 0;  // On Efface la tuile avec laquelle on a fusionné.
            }
        }

        // On Compresse la ligne pour éliminer les cases vides créées après la fusion ou déjà présentes.
        int indice_cible = 0;  // Cible pour le déplacement des tuiles non vides.
        for (int j = 0; j < g.table.at(i).size(); j=j+1) {
            if (g.table.at(i).at(j) != 0) {
                if (j != indice_cible) {
                    g.table.at(i).at(indice_cible) = g.table.at(i).at(j);
                    g.table.at(i).at(j) = 0;
                    mouvement = true;
                }
                indice_cible=indice_cible+1;
            }
        }
    }

    // On Retourne le nombre de cases vides après un mouvement réussi, ou -1 si aucun changement n'a été fait.
    if (mouvement) {
        return vides(g);  // On Calcule et retourne le nombre de cases vides dans la grille.
    } else {
        return -1;  // Aucun mouvement n'a été fait, donc on retourne -1.
    }
}


int haut(Grille &g) {
    bool mouvement = false;  // Pour suivre si un mouvement ou une fusion a été réalisé

    // On Parcoure la grille colonne par colonne
    for (int j = 0; j < g.table.size(); j=j+1) {
        // On Combine les tuiles lorsque deux valeurs adjacentes sont égales (en ignorant les zéros)
        for (int i = 0; i < g.table.size() - 1; i=i+1) {
            if (g.table.at(i).at(j) == 0) continue;  // On Ignore les cases vides

            // On Trouve la prochaine tuile non vide vers le bas
            int k;
            for (k = 1; (i + k) < g.table.size() and g.table.at(i + k).at(j) == 0; k=k+1);

            // On Vérifie si la case actuelle peut fusionner avec cette case non vide trouvée
            if ((i + k) < g.table.size() and g.table.at(i).at(j) == g.table.at(i + k).at(j)) {
                mouvement = true;
                g.table.at(i).at(j) *= 2;  // On Fusionne les tuiles
                g.score += g.table.at(i).at(j);  // On met à jour le score
                g.table.at(i + k).at(j) = 0;  // On Efface la tuile fusionnée
            }
        }

        // On compresse les tuiles vers le haut pour éliminer les espaces vides
        int indice_cible = 0;
        for (int i = 0; i < g.table.size(); i=i+1) {
            if (g.table.at(i).at(j) != 0) {
                if (i != indice_cible) {
                    g.table.at(indice_cible).at(j) = g.table.at(i).at(j);  // Déplacer la tuile vers le haut
                    g.table.at(i).at(j) = 0;
                    mouvement = true;
                }
                indice_cible=indice_cible+1;
            }
        }
    }

    // On Retourne le nombre de cases vides après un mouvement réussi ou -1 si aucun changement n'a été fait
    if (mouvement) {
        return vides(g);  // On Calcule et retourne le nombre de cases vides dans la grille.
    } else {
        return -1;  // Aucun mouvement n'a été fait, donc on retourne -1.
    }
}


int bas(Grille &g) {
    bool mouvement = false;  // Indique si un mouvement ou une fusion a été réalisé.

    // On Parcoure chaque colonne de la grille de bas en haut.
    for (int j = 0; j < g.table.size(); j=j+1) {
        int positionCible = g.table.size() - 1;  // On Démarrer à la dernière rangée, se préparant à compresser vers le bas.

        // On Compresse toutes les tuiles vers le bas.
        for (int i = g.table.size() - 1; i >= 0; i=i-1) {
            if (g.table.at(i).at(j) != 0) {  // On Vérifie si la case actuelle n'est pas vide.
                g.table.at(positionCible).at(j) = g.table.at(i).at(j);  // On Déplace la tuile vers la position cible.
                if (positionCible != i) {  // On Vérifie si la tuile a été déplacée.
                    g.table.at(i).at(j) = 0;  // On Efface l'ancien emplacement de la tuile.
                    mouvement = true;  // On marque qu'un mouvement a été effectué.
                }
                positionCible=positionCible-1;  // On Décrémente la position cible pour la prochaine tuile potentiellement mobile.
            }
        }

        // On fusionne les tuiles consécutives identiques.
        for (int i = g.table.size() - 1; i > 0; i--) {
            if (g.table.at(i).at(j) != 0 and g.table.at(i).at(j) == g.table.at(i - 1).at(j)) {  // Vérifier si deux tuiles consécutives sont identiques.
                g.table.at(i).at(j) *= 2;  // On Double la valeur de la tuile en bas.
                g.score += g.table.at(i).at(j);  // On Ajoute cette valeur doublée au score total.
                g.table.at(i - 1).at(j) = 0;  //  On Efface la tuile fusionnée au-dessus.
                mouvement = true;  // On Confirme qu'une fusion a eu lieu.
                i=i-1;  // On Saute la tuile au-dessus pour éviter une fusion multiple dans une même opération.
            }
        }
    }

    // On Détermine le résultat de la fonction basé sur la présence ou l'absence de mouvements.
    if (mouvement) {
        return vides(g);  // On Calcule et retourner le nombre de cases vides restantes si des mouvements ont été effectués.
    } else {
        return -1;  // On Retourne -1 si aucun mouvement n'a été possible, indiquant une grille pleine ou immobilisée.
    }
}


void affiche (const Grille &g) {
  int i, j, k;
  int max = dimension(g);
  cout << endl << " \t ";
  for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
  cout << endl;
  /* Verifier si on veut que la ligne du haut soit 0 ou max-1 */
  for(i = 0; i < max; i = i+1) {
    cout << "\t|";
    for(j=0; j < max; j=j+1) {
      if(g.table.at(i).at(j) == 0) {
	cout << "      |";
      } else { cout << " " << setw(4) << g.table.at(i).at(j) << " |" ; }
    }
    if (i != max-1) {
      cout << endl << "\t|";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << "|" << endl;
    } else {
      cout << endl << "\t ";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << endl;
    }
  }
  cout << endl << "Score: " << score(g) << ", Vides: " << vides(g) << endl;
}
