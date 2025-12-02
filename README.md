# 🎮 Le Jeu de la Vie de Conway - Version Améliorée 1.1.0

[🇫🇷 Version française](#-version-française) | [🇬🇧 English Version](#-english-version)

---

<p align="center">
  <img src="screenshots/01_main_interface.png" alt="Interface principale" width="600"/>
</p>

---

## 🇫🇷 Version Française

### 📖 Table des matières
- [À propos du projet](#-à-propos-du-projet)
- [Fonctionnalités](#-fonctionnalités)
- [Captures d'écran](#-captures-décran)
- [Installation](#-installation)
- [Guide d'utilisation](#-guide-dutilisation)
- [Architecture technique](#-architecture-technique)
- [Compilation depuis les sources](#-compilation-depuis-les-sources)
- [Réponse aux exigences du projet](#-réponse-aux-exigences-du-projet)
- [Documentation](#-documentation)
- [Licence](#-licence)

---

### 🎯 À propos du projet

Ce projet est une **implémentation complète et améliorée** du célèbre **Jeu de la Vie de John Conway**, développée dans le cadre d'un projet de Programmation Orientée Objet en C++.

#### Qu'est-ce que le Jeu de la Vie ?

Le **Jeu de la Vie** est un automate cellulaire imaginé par le mathématicien John Conway en 1970. C'est un jeu à "zéro joueur" où l'évolution est déterminée par son état initial.

**Règles du jeu :**
- Les cellules vivent sur une **grille bidimensionnelle**
- Chaque cellule peut être **vivante (1)** ou **morte (0)**
- Chaque cellule a **8 voisins** (les cellules adjacentes horizontalement, verticalement et en diagonale)

**Règles de transition :**
1. Une cellule morte avec **exactement 3 voisines vivantes** devient vivante (naissance)
2. Une cellule vivante avec **2 ou 3 voisines vivantes** reste vivante (survie)
3. Dans tous les autres cas, la cellule meurt ou reste morte (surpopulation ou sous-population)

Malgré la simplicité de ces règles, le Jeu de la Vie produit des comportements extraordinairement complexes et des motifs fascinants !

---

### ✨ Fonctionnalités

#### 🎨 Interface & Visualisation
- **8 thèmes de couleurs** magnifiques (Néon, Océan, Forêt, Coucher de soleil, Lavande, Arc-en-ciel, Feu, Glace)
- **Interface moderne** avec panneaux semi-transparents
- **Visualisation de l'âge des cellules** - les cellules changent de couleur selon leur ancienneté
- **Grille personnalisable** - activable/désactivable
- **Panneau de statistiques en temps réel** :
  - Numéro de génération
  - Population actuelle
  - Naissances et décès
  - Population max/min/moyenne
  - FPS et vitesse
- **Mini-carte** pour navigation sur grandes grilles
- **Aide contextuelle** avec tous les contrôles

#### 🎮 Gameplay & Interaction
- **Générateur de motifs 3×3 aléatoires** (4-9 cellules vivantes) - Touche `R`
- **Système de voyage dans le temps** :
  - ← Retour arrière dans l'historique
  - → Avance dans l'historique
  - Génération remise à 0 lors de la navigation
- **Pause automatique intelligente** :
  - Détecte les oscillateurs (motifs périodiques)
  - Détecte les natures mortes (motifs stables)
  - Pause automatique après 3 générations stables
- **Détection de motifs classiques** :
  - Block (nature morte)
  - Beehive (ruche)
  - Blinker (oscillateur période 2)
  - Toad (crapaud, oscillateur période 2)
  - Beacon (phare, oscillateur période 2)
  - Glider (planeur)
- **Dessin interactif** - cliquez pour placer/retirer des cellules
- **Panoramique & Zoom** - naviguez facilement dans de grandes grilles
- **Contrôle de vitesse** - ajustez la vitesse de simulation

#### 🔧 Caractéristiques techniques
- **Principes SOLID** appliqués rigoureusement
- **Architecture POO propre** :
  - Séparation logique/rendu
  - Encapsulation des responsabilités
  - Abstraction des composants
- **Système de détection de motifs** avec hachage d'états
- **Historique des générations** pour voyage temporel
- **Rendu optimisé** avec SFML 3.0
- **Grille configurable** (taille personnalisable)
- **Multi-plateforme** (Windows, Linux, macOS)

---

### 📸 Captures d'écran

<p align="center">
  <img src="screenshots/01_main_interface.png" alt="Interface principale" width="45%"/>
  <img src="screenshots/02_pattern.png" alt="Motif généré" width="45%"/>
</p>

<p align="center">
  <img src="screenshots/03_evolution.png" alt="Évolution" width="45%"/>
  <img src="screenshots/04_theme.png" alt="Thèmes" width="45%"/>
</p>

<p align="center">
  <img src="screenshots/05_help.png" alt="Aide" width="45%"/>
</p>

---

### 💾 Installation

#### Option 1 : Installateur Windows (Recommandé)
1. Téléchargez `GameOfLife_Setup_v1.1.0.exe` depuis [Releases](https://github.com/votreusername/GameOfLife/releases)
2. Exécutez l'installateur
3. Suivez les instructions de l'assistant d'installation
4. Lancez depuis le Menu Démarrer ou le raccourci Bureau

#### Option 2 : Version portable
1. Téléchargez `GameOfLife_v1.1.0_Portable.zip`
2. Extrayez dans le dossier de votre choix
3. Exécutez `GameOfLife.exe`

#### Configuration requise
- **OS** : Windows 10/11, Linux (Ubuntu 20.04+), macOS 10.15+
- **RAM** : 512 MB minimum
- **Processeur** : Compatible x64
- **Graphiques** : Support OpenGL 3.3+

---

### 🎯 Guide d'utilisation

#### Contrôles principaux

| Touche | Action | Description |
|--------|--------|-------------|
| **R** | Nouveau motif | Génère un motif aléatoire 3×3 (4-9 cellules) au centre |
| **ESPACE** | Lecture/Pause | Lance ou met en pause la simulation |
| **N** | Génération suivante | Avance d'une génération (en pause) |
| **C** | Effacer | Vide complètement la grille |
| **←** | Retour arrière | Revient à la génération précédente (Gen → 0) |
| **→** | Avancer | Avance dans l'historique (Gen → 0) |
| **O** | Auto-pause | Active/désactive la pause automatique |
| **K** | Changer thème | Parcourt les 8 thèmes de couleurs |
| **A** | Âge des cellules | Active/désactive la visualisation de l'âge |
| **G** | Grille | Affiche/masque les lignes de grille |
| **S** | Statistiques | Affiche/masque le panneau de stats |
| **M** | Mini-carte | Affiche/masque la mini-carte |
| **H** | Aide | Affiche/masque l'overlay d'aide |
| **F** | Remplissage aléatoire | Remplit la grille (densité 10%) |
| **I** | Inverser | Inverse toutes les cellules |
| **+/-** | Vitesse | Ajuste la vitesse de simulation |
| **ESC** | Quitter | Ferme l'application |

#### Contrôles souris

| Action | Description |
|--------|-------------|
| **Clic gauche** | Place/retire une cellule |
| **Glisser droit** | Déplace la vue (panoramique) |
| **Molette** | Zoom avant/arrière |

#### Démarrage rapide

1. **Lancez l'application**
2. **Appuyez sur R** pour générer un motif aléatoire
3. **Appuyez sur ESPACE** pour démarrer
4. **Observez l'évolution !**
5. Expérimentez avec :
   - **K** pour changer de thème
   - **←** et **→** pour naviguer dans l'historique
   - **A** pour voir l'âge des cellules

#### Motifs classiques à essayer

Vous pouvez dessiner ces motifs célèbres :

**Block (Nature morte)** :
```
██
██
```

**Blinker (Oscillateur période 2)** :
```
███
```

**Glider (Planeur)** :
```
 █
  █
███
```

---

### 🏗️ Architecture technique

Le projet suit une **architecture POO propre** respectant les **principes SOLID** :

```
GameOfLife_v1.1.0/
├── src/                      # Code source
│   ├── Grid.cpp              # Gestion de la grille
│   ├── GameEngine.cpp        # Moteur de jeu & règles
│   ├── EnhancedGUIRenderer.cpp # Rendu graphique
│   ├── PatternDetector.cpp   # Détection de motifs
│   ├── PatternLibrary.cpp    # Base de motifs
│   └── TimelineManager.cpp   # Gestion historique
│
├── include/                  # Fichiers d'en-tête
│   ├── Grid.hpp
│   ├── GameEngine.hpp
│   ├── EnhancedGUIRenderer.hpp
│   ├── PatternDetector.hpp
│   ├── PatternLibrary.hpp
│   ├── TimelineManager.hpp
│   ├── Config.hpp            # Configuration
│   ├── Statistics.hpp        # Statistiques
│   └── UIButton.hpp          # Composants UI
│
├── docs/                     # Documentation
│   ├── ARCHITECTURE.md       # Architecture détaillée
│   ├── SOLID_PRINCIPLES.md   # Principes SOLID
│   ├── USER_GUIDE_FR.md      # Guide utilisateur français
│   └── USER_GUIDE_EN.md      # Guide utilisateur anglais
│
├── screenshots/              # Captures d'écran
├── installer/                # Script installateur
├── Makefile                  # Build système
├── README.md                 # Ce fichier
├── LICENSE                   # Licence MIT
└── .gitignore               # Fichiers ignorés Git
```

#### Principes de conception appliqués

##### 1. **Single Responsibility Principle (SRP)**
Chaque classe a une responsabilité unique :
- `Grid` : Gère uniquement les données de la grille
- `GameEngine` : Applique les règles du jeu
- `EnhancedGUIRenderer` : Gère l'affichage et les interactions
- `PatternDetector` : Détecte les motifs stables

##### 2. **Open/Closed Principle (OCP)**
Le système est ouvert à l'extension :
- Ajout de nouveaux thèmes sans modifier le code existant
- Nouveaux détecteurs de motifs ajoutables facilement

##### 3. **Liskov Substitution Principle (LSP)**
Les abstractions sont utilisables de manière interchangeable

##### 4. **Interface Segregation Principle (ISP)**
Interfaces minimales et ciblées pour chaque composant

##### 5. **Dependency Inversion Principle (DIP)**
Dépendance sur des abstractions, pas sur des implémentations concrètes

Pour plus de détails, voir [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)

---

### 🔨 Compilation depuis les sources

#### Prérequis

- **Compilateur C++20** : GCC 10+, Clang 10+, ou MSVC 2019+
- **SFML 3.0** : Bibliothèque graphique
- **Make** : Système de build

#### Windows (MSYS2/MinGW64)

```bash
# 1. Installer MSYS2 depuis https://www.msys2.org/

# 2. Ouvrir MSYS2 MinGW 64-bit terminal

# 3. Installer les dépendances
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-sfml mingw-w64-x86_64-make

# 4. Cloner le dépôt
git clone https://github.com/votreusername/GameOfLife.git
cd GameOfLife

# 5. Compiler
make

# 6. Exécuter
./GameOfLife.exe
```

#### Linux (Ubuntu/Debian)

```bash
# 1. Installer les dépendances
sudo apt update
sudo apt install build-essential libsfml-dev git

# 2. Cloner le dépôt
git clone https://github.com/votreusername/GameOfLife.git
cd GameOfLife

# 3. Compiler
make

# 4. Exécuter
./GameOfLife
```

#### macOS

```bash
# 1. Installer Homebrew (si nécessaire)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 2. Installer les dépendances
brew install sfml

# 3. Cloner le dépôt
git clone https://github.com/votreusername/GameOfLife.git
cd GameOfLife

# 4. Compiler
make

# 5. Exécuter
./GameOfLife
```

#### Options de compilation

```bash
make          # Compilation standard
make clean    # Nettoyage
make rebuild  # Recompilation complète
make release  # Build optimisé pour distribution
```

---

### 📋 Réponse aux exigences du projet

Ce projet répond intégralement aux exigences du sujet **"Projet POO : Le Jeu de la Vie"**.

#### ✅ Mode Console : Objectifs et attendus

**Classe Grid** :
- [x] Représentation de la grille 2D
- [x] Gestion des états des cellules (vivante/morte)
- [x] Comptage des voisins avec topologie à 8 voisins
- [x] Méthodes d'accès et de modification
- [x] Affichage console (via `printGrid()`)

**Classe GameEngine** :
- [x] Application des règles de Conway
- [x] Calcul de la génération suivante
- [x] Gestion de l'état du jeu
- [x] Compteur de générations
- [x] Détection de stabilité

**Main console** :
- [x] Initialisation de la grille
- [x] Boucle de simulation
- [x] Affichage des générations successives

#### ✅ Mode Graphique : Objectifs et attendus

**Rendu graphique avec SFML** :
- [x] Affichage temps réel de la grille
- [x] Cellules vivantes colorées selon le thème
- [x] Grille visible/masquable
- [x] Animation fluide

**Interaction utilisateur** :
- [x] Clavier :
  - Play/pause (ESPACE)
  - Génération suivante (N)
  - Reset (R avec génération aléatoire)
  - Clear (C)
  - Changement de thème (K)
- [x] Souris :
  - Dessiner des cellules (clic gauche)
  - Panoramique (glisser droit)
  - Zoom (molette)

**Interface utilisateur** :
- [x] Panneaux d'information (stats, mini-carte)
- [x] Overlay d'aide (H)
- [x] Compteurs (génération, population, FPS)
- [x] Thèmes visuels multiples

#### ✅ Principes POO appliqués

**Encapsulation** :
- [x] Données privées dans chaque classe
- [x] Accès contrôlé via getters/setters
- [x] État interne protégé

**Abstraction** :
- [x] Interfaces claires et minimales
- [x] Séparation logique/présentation
- [x] Masquage de la complexité

**Séparation des responsabilités** :
- [x] Grid gère uniquement les données
- [x] GameEngine gère la logique
- [x] Renderer gère l'affichage
- [x] PatternDetector gère la détection

**Principes SOLID** :
- [x] Single Responsibility
- [x] Open/Closed
- [x] Liskov Substitution
- [x] Interface Segregation
- [x] Dependency Inversion

Voir [docs/SOLID_PRINCIPLES.md](docs/SOLID_PRINCIPLES.md) pour analyse détaillée.

#### ✅ Fonctionnalités bonus implémentées

- [x] **Multiples thèmes** (8 thèmes différents)
- [x] **Détection de motifs** (oscillateurs, natures mortes)
- [x] **Historique** avec voyage temporel
- [x] **Statistiques avancées** (naissances, décès, populations)
- [x] **Pause automatique** sur motifs stables
- [x] **Visualisation âge des cellules**
- [x] **Mini-carte** de navigation
- [x] **Génération aléatoire** avec motifs 3×3
- [x] **Zoom et panoramique**
- [x] **Bibliothèque de motifs** classiques

---

### 📚 Documentation

Documentation complète disponible dans le dossier `docs/` et à la racine :

#### 📖 Guides Principaux
- **[SETUP_SFML_AND_DLLS.md](SETUP_SFML_AND_DLLS.md)** : ⭐ **Comment j'ai configuré SFML et les DLLs** (Guide complet FR/EN)
- **[ANSWERS_TO_YOUR_QUESTIONS.md](ANSWERS_TO_YOUR_QUESTIONS.md)** : Réponses détaillées aux questions fréquentes

#### 🏗️ Architecture & Design
- **[ARCHITECTURE.md](docs/ARCHITECTURE.md)** : Architecture détaillée du système
- **[SOLID_PRINCIPLES.md](docs/SOLID_PRINCIPLES.md)** : Application des principes SOLID avec exemples de code

#### 📘 Guides Utilisateur & Développeur
- **[BUILDING.md](docs/BUILDING.md)** : Instructions de compilation avancées (Windows/Linux/macOS)
- **[CONTRIBUTING.md](docs/CONTRIBUTING.md)** : Guide de contribution au projet
- **[INSTALLATION_INFO.txt](docs/INSTALLATION_INFO.txt)** : Guide d'installation (bilingue FR/EN)
- **[QUICK_START.txt](docs/QUICK_START.txt)** : Démarrage rapide pour nouveaux utilisateurs

#### 📦 Package & Distribution
- **[CHANGELOG.md](CHANGELOG.md)** : Historique des versions
- **[LICENSE](LICENSE)** : Licence MIT

---

### 📄 Licence

Ce projet est sous licence MIT. Voir [LICENSE](LICENSE) pour plus de détails.

```
MIT License

Copyright (c) 2025 [Votre Nom]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

---

### 👨‍💻 Auteur

**[Votre Nom]**
- Email : votre.email@example.com
- GitHub : [@votreusername](https://github.com/votreusername)

---

### 🙏 Remerciements

- **John Conway** pour l'invention du Jeu de la Vie
- **SFML Team** pour l'excellente bibliothèque graphique
- **Communauté C++** pour les ressources et le support

---

### 📞 Support

Pour toute question, problème ou suggestion :
- Ouvrez une [Issue](https://github.com/votreusername/GameOfLife/issues)
- Consultez la [Documentation](docs/)
- Contactez-moi par email

---

**Bon jeu ! 🎮✨**

---

## 🇬🇧 English Version

### 📖 Table of Contents
- [About the Project](#-about-the-project)
- [Features](#-features)
- [Screenshots](#-screenshots-1)
- [Installation](#-installation-1)
- [User Guide](#-user-guide)
- [Technical Architecture](#-technical-architecture-1)
- [Building from Source](#-building-from-source-1)
- [Project Requirements](#-project-requirements-compliance)
- [Documentation](#-documentation-1)
- [License](#-license-1)

---

### 🎯 About the Project

This project is a **complete and enhanced implementation** of **John Conway's Game of Life**, developed as part of an Object-Oriented Programming project in C++.

#### What is the Game of Life?

The **Game of Life** is a cellular automaton devised by mathematician John Conway in 1970. It's a "zero-player game" where evolution is determined by its initial state.

**Game Rules:**
- Cells live on a **two-dimensional grid**
- Each cell can be **alive (1)** or **dead (0)**
- Each cell has **8 neighbors** (adjacent cells horizontally, vertically, and diagonally)

**Transition Rules:**
1. A dead cell with **exactly 3 living neighbors** becomes alive (birth)
2. A living cell with **2 or 3 living neighbors** stays alive (survival)
3. In all other cases, the cell dies or remains dead (overpopulation or underpopulation)

Despite the simplicity of these rules, the Game of Life produces extraordinarily complex behaviors and fascinating patterns!

---

### ✨ Features

#### 🎨 Interface & Visualization
- **8 beautiful color themes** (Neon, Ocean, Forest, Sunset, Lavender, Rainbow, Fire, Ice)
- **Modern interface** with semi-transparent panels
- **Cell age visualization** - cells change color based on longevity
- **Customizable grid** - toggle on/off
- **Real-time statistics panel**:
  - Generation number
  - Current population
  - Births and deaths
  - Max/min/average population
  - FPS and speed
- **Mini-map** for navigation on large grids
- **Contextual help** with all controls

#### 🎮 Gameplay & Interaction
- **Random 3×3 pattern generator** (4-9 living cells) - Press `R`
- **Time travel system**:
  - ← Rewind through history
  - → Forward through history
  - Generation reset to 0 when navigating
- **Intelligent auto-pause**:
  - Detects oscillators (periodic patterns)
  - Detects still lifes (stable patterns)
  - Auto-pause after 3 stable generations
- **Classic pattern detection**:
  - Block (still life)
  - Beehive
  - Blinker (period 2 oscillator)
  - Toad (period 2 oscillator)
  - Beacon (period 2 oscillator)
  - Glider
- **Interactive drawing** - click to place/remove cells
- **Pan & Zoom** - easily navigate large grids
- **Speed control** - adjust simulation speed

#### 🔧 Technical Features
- **SOLID principles** rigorously applied
- **Clean OOP architecture**:
  - Logic/rendering separation
  - Responsibility encapsulation
  - Component abstraction
- **Pattern detection system** with state hashing
- **Generation history** for time travel
- **Optimized rendering** with SFML 3.0
- **Configurable grid** (customizable size)
- **Cross-platform** (Windows, Linux, macOS)

---

### 📸 Screenshots

<p align="center">
  <img src="screenshots/01_main_interface.png" alt="Main interface" width="45%"/>
  <img src="screenshots/02_pattern.png" alt="Generated pattern" width="45%"/>
</p>

<p align="center">
  <img src="screenshots/03_evolution.png" alt="Evolution" width="45%"/>
  <img src="screenshots/04_theme.png" alt="Themes" width="45%"/>
</p>

<p align="center">
  <img src="screenshots/05_help.png" alt="Help" width="45%"/>
</p>

---

### 💾 Installation

#### Option 1: Windows Installer (Recommended)
1. Download `GameOfLife_Setup_v1.1.0.exe` from [Releases](https://github.com/yourusername/GameOfLife/releases)
2. Run the installer
3. Follow the installation wizard instructions
4. Launch from Start Menu or Desktop shortcut

#### Option 2: Portable Version
1. Download `GameOfLife_v1.1.0_Portable.zip`
2. Extract to folder of your choice
3. Run `GameOfLife.exe`

#### System Requirements
- **OS**: Windows 10/11, Linux (Ubuntu 20.04+), macOS 10.15+
- **RAM**: 512 MB minimum
- **Processor**: x64 compatible
- **Graphics**: OpenGL 3.3+ support

---

### 🎯 User Guide

#### Main Controls

| Key | Action | Description |
|-----|--------|-------------|
| **R** | New pattern | Generates random 3×3 pattern (4-9 cells) at center |
| **SPACE** | Play/Pause | Starts or pauses simulation |
| **N** | Next generation | Advances one generation (when paused) |
| **C** | Clear | Completely clears the grid |
| **←** | Rewind | Returns to previous generation (Gen → 0) |
| **→** | Forward | Advances through history (Gen → 0) |
| **O** | Auto-pause | Toggles automatic pause |
| **K** | Change theme | Cycles through 8 color themes |
| **A** | Cell age | Toggles age visualization |
| **G** | Grid | Shows/hides grid lines |
| **S** | Statistics | Shows/hides stats panel |
| **M** | Mini-map | Shows/hides mini-map |
| **H** | Help | Shows/hides help overlay |
| **F** | Random fill | Fills grid (10% density) |
| **I** | Invert | Inverts all cells |
| **+/-** | Speed | Adjusts simulation speed |
| **ESC** | Quit | Closes application |

#### Mouse Controls

| Action | Description |
|--------|-------------|
| **Left click** | Places/removes a cell |
| **Right drag** | Moves the view (pan) |
| **Scroll wheel** | Zoom in/out |

#### Quick Start

1. **Launch the application**
2. **Press R** to generate a random pattern
3. **Press SPACE** to start
4. **Watch the evolution!**
5. Experiment with:
   - **K** to change themes
   - **←** and **→** to navigate history
   - **A** to see cell ages

---

### 🏗️ Technical Architecture

The project follows a **clean OOP architecture** respecting **SOLID principles**:

For full architecture details, see [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)

---

### 🔨 Building from Source

#### Prerequisites

- **C++20 compiler**: GCC 10+, Clang 10+, or MSVC 2019+
- **SFML 3.0**: Graphics library
- **Make**: Build system

#### Windows (MSYS2/MinGW64)

```bash
# 1. Install MSYS2 from https://www.msys2.org/

# 2. Open MSYS2 MinGW 64-bit terminal

# 3. Install dependencies
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-sfml mingw-w64-x86_64-make

# 4. Clone repository
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife

# 5. Build
make

# 6. Run
./GameOfLife.exe
```

#### Linux (Ubuntu/Debian)

```bash
# 1. Install dependencies
sudo apt update
sudo apt install build-essential libsfml-dev git

# 2. Clone and build
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife
make

# 3. Run
./GameOfLife
```

#### macOS

```bash
# 1. Install dependencies
brew install sfml

# 2. Clone and build
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife
make

# 3. Run
./GameOfLife
```

---

### 📋 Project Requirements Compliance

This project fully complies with the **"OOP Project: Game of Life"** requirements.

For detailed compliance, see the French section above or [docs/PROJECT_REQUIREMENTS.md](docs/PROJECT_REQUIREMENTS.md)

#### ✅ Console Mode: Complete
- [x] Grid class with 2D cell management
- [x] GameEngine with Conway's rules
- [x] Neighbor counting (8-neighbor topology)
- [x] Console display functionality

#### ✅ Graphical Mode: Complete
- [x] SFML real-time rendering
- [x] User interaction (keyboard & mouse)
- [x] UI panels and overlays
- [x] Multiple visual themes

#### ✅ OOP Principles: Fully Applied
- [x] Encapsulation
- [x] Abstraction
- [x] Separation of Concerns
- [x] SOLID Principles

See [docs/SOLID_PRINCIPLES.md](docs/SOLID_PRINCIPLES.md) for detailed analysis.

---

### Documentation

Complete documentation available in `docs/` folder and root directory:

#### 📖 Main Guides
- **[SETUP_SFML_AND_DLLS.md](SETUP_SFML_AND_DLLS.md)**: ⭐ **How I configured SFML and DLLs** (Complete Guide FR/EN)
- **[ANSWERS_TO_YOUR_QUESTIONS.md](ANSWERS_TO_YOUR_QUESTIONS.md)**: Detailed answers to frequently asked questions

#### Architecture & Design
- **[ARCHITECTURE.md](docs/ARCHITECTURE.md)**: Detailed system architecture
- **[SOLID_PRINCIPLES.md](docs/SOLID_PRINCIPLES.md)**: SOLID principles application with code examples

#### User & Developer Guides
- **[BUILDING.md](docs/BUILDING.md)**: Advanced build instructions (Windows/Linux/macOS)
- **[CONTRIBUTING.md](docs/CONTRIBUTING.md)**: Contribution guidelines
- **[INSTALLATION_INFO.txt](docs/INSTALLATION_INFO.txt)**: Installation guide (bilingual FR/EN)
- **[QUICK_START.txt](docs/QUICK_START.txt)**: Quick start for new users

#### Verification & Compliance
- **[EXAM_VERIFICATION_CHECKLIST.md](EXAM_VERIFICATION_CHECKLIST.md)**: Complete exam requirements verification
- **[EXAM_REQUIREMENTS_SUMMARY.md](EXAM_REQUIREMENTS_SUMMARY.md)**: Academic project requirements summary

#### Package & Distribution
- **[PACKAGE_COMPLETE.md](PACKAGE_COMPLETE.md)**: Complete package summary
- **[CHANGELOG.md](CHANGELOG.md)**: Version history
- **[LICENSE](LICENSE)**: MIT License

---

### License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

### 👨‍💻 Author

**[Your Name]**
- Email: your.email@example.com
- GitHub: [@yourusername](https://github.com/yourusername)

---

### 🙏 Acknowledgments

- **John Conway** for inventing the Game of Life
- **SFML Team** for the excellent graphics library
- **C++ Community** for resources and support

---

### 📞 Support

For questions, issues, or suggestions:
- Open an [Issue](https://github.com/yourusername/GameOfLife/issues)
- Check the [Documentation](docs/)
- Contact me by email

---

**Happy Gaming! 🎮✨**
