# 🔢 2048 en C++ – Jeu de console interactif

![Aperçu du jeu 2048](./assets/screenshot.png) <!-- Remplace par ton image -->

## 📝 Description

Jeu **2048** en mode **console** entièrement codé en **C++**.  
Le joueur déplace les tuiles avec les touches `h`, `b`, `g`, `d` (haut, bas, gauche, droite) dans le but d’atteindre une tuile avec la valeur cible (par défaut 2048).

Le jeu inclut :
- Une interface texte propre
- Une logique de mouvement/fusion comme dans le vrai 2048
- Une grille dynamique (taille personnalisable)
- Des tests automatiques pour valider le fonctionnement
- Un système de score

---

## 🚀 Fonctionnalités

- 🎯 Objectif personnalisable (ex : 2048, 4096…)
- 📏 Grille personnalisable (4x4, 5x5, etc.)
- 🧠 Logique complète du jeu (mouvements, fusions, fin de partie)
- 🧪 Fonctions de test intégrées (`testFV()`)
- 🔄 Partie rejouable en boucle
- 👥 Projet en collaboration avec répartition des tâches

---

## 🛠️ Technologies utilisées

- [C++](https://fr.cppreference.com/w/) – langage principal
- [Makefile](https://www.gnu.org/software/make/manual/make.html) – pour compiler facilement
- [iostream](https://en.cppreference.com/w/cpp/header/iostream) – entrées/sorties
- [vector](https://en.cppreference.com/w/cpp/container/vector) – structure de données
- [cassert](https://en.cppreference.com/w/cpp/header/cassert) – assertions
- [cstdlib](https://en.cppreference.com/w/cpp/header/cstdlib), [ctime](https://en.cppreference.com/w/cpp/header/ctime) – aléatoire

---

## ⚙️ Comment utiliser ce projet

```bash
# 1. Cloner le dépôt
git clone https://github.com/ton-user/2048-cpp.git
cd 2048-cpp

# 2. Compiler le projet
make

# 3. Lancer le jeu
./jeu

# 4. (Optionnel) Exécuter uniquement les tests
./jeu_test
