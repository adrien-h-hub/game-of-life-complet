# 🛠️ Configuration SFML et DLLs - Guide Complet

## 🇫🇷 Version Française

### 📋 Table des matières
- [Introduction](#introduction)
- [Installation de SFML 3.0](#installation-de-sfml-30)
- [Configuration des DLLs](#configuration-des-dlls)
- [Résolution de problèmes](#résolution-de-problèmes)
- [Compilation du projet](#compilation-du-projet)

---

## Introduction

Ce document explique **comment j'ai configuré SFML 3.0 et les DLLs** pour le projet Game of Life. Si vous rencontrez des erreurs comme "Le programme ne peut pas démarrer car sfml-graphics-3.dll est introuvable", ce guide vous aidera.

---

## 📦 Installation de SFML 3.0

### Méthode 1: MSYS2 (Recommandé pour Windows)

**C'est la méthode que j'ai utilisée pour ce projet.**

#### 1. Installer MSYS2

1. Télécharger MSYS2 depuis https://www.msys2.org/
2. Installer dans `C:\msys64` (chemin par défaut)
3. Lancer **MSYS2 MinGW 64-bit**

#### 2. Mettre à jour MSYS2

```bash
pacman -Syu
# Fermer et rouvrir le terminal si demandé
pacman -Su
```

#### 3. Installer les outils de développement

```bash
# Compilateur C++
pacman -S mingw-w64-x86_64-gcc

# Make
pacman -S mingw-w64-x86_64-make

# SFML 3.0
pacman -S mingw-w64-x86_64-sfml
```

#### 4. Vérifier l'installation

```bash
g++ --version
# Doit afficher GCC 12.x ou plus récent

pkg-config --modversion sfml-all
# Doit afficher 3.0.0 ou similaire
```

#### 5. Localisation des fichiers SFML

Après l'installation, SFML se trouve dans:
- **Headers (.hpp)**: `C:\msys64\mingw64\include\SFML\`
- **Bibliothèques (.a)**: `C:\msys64\mingw64\lib\`
- **DLLs (.dll)**: `C:\msys64\mingw64\bin\`

---

### Méthode 2: Installation manuelle (Alternative)

1. Télécharger SFML 3.0 depuis https://www.sfml-dev.org/download/sfml/3.0.0/
2. Choisir la version **GCC MinGW (SEH) - 64-bit**
3. Extraire dans `C:\SFML-3.0.0\`
4. Configurer les chemins dans votre IDE/Makefile

---

## 🔧 Configuration des DLLs

### Problème: "sfml-graphics-3.dll introuvable"

Quand vous lancez le `.exe`, Windows cherche les DLLs dans cet ordre:
1. Le dossier du `.exe`
2. Les dossiers système (`C:\Windows\System32`)
3. Les dossiers dans la variable `PATH`

### Solution 1: Copier les DLLs à côté de l'exécutable (Ma méthode)

**C'est ce que j'ai fait pour ce projet** - la méthode la plus simple et portable.

#### Étape 1: Identifier les DLLs nécessaires

Pour ce projet, j'ai besoin de:
```
libsfml-graphics-3.dll    ← Rendu graphique
libsfml-window-3.dll      ← Gestion de fenêtre
libsfml-system-3.dll      ← Système (threads, time)
libgcc_s_seh-1.dll        ← Runtime GCC
libstdc++-6.dll           ← Runtime C++ standard
libwinpthread-1.dll       ← Support threading Windows
```

#### Étape 2: Localiser les DLLs

Avec MSYS2, elles sont dans:
```
C:\msys64\mingw64\bin\
```

#### Étape 3: Copier automatiquement (PowerShell)

J'ai créé un script PowerShell pour copier les DLLs:

```powershell
# copy_dlls.ps1
$sfmlPath = "C:\msys64\mingw64\bin"
$targetPath = ".\bin"

# DLLs SFML
Copy-Item "$sfmlPath\libsfml-graphics-3.dll" -Destination $targetPath
Copy-Item "$sfmlPath\libsfml-window-3.dll" -Destination $targetPath
Copy-Item "$sfmlPath\libsfml-system-3.dll" -Destination $targetPath

# DLLs GCC Runtime
Copy-Item "$sfmlPath\libgcc_s_seh-1.dll" -Destination $targetPath
Copy-Item "$sfmlPath\libstdc++-6.dll" -Destination $targetPath
Copy-Item "$sfmlPath\libwinpthread-1.dll" -Destination $targetPath

Write-Host "✅ DLLs copiées avec succès!"
```

Exécuter:
```powershell
.\copy_dlls.ps1
```

#### Étape 4: Vérifier la structure

Après copie, votre dossier doit ressembler à:
```
bin/
├── GameOfLife.exe               ← Exécutable
├── libsfml-graphics-3.dll       ← DLL SFML
├── libsfml-window-3.dll
├── libsfml-system-3.dll
├── libgcc_s_seh-1.dll           ← Runtime GCC
├── libstdc++-6.dll
└── libwinpthread-1.dll
```

---

### Solution 2: Ajouter MSYS2 au PATH (Système)

**Alternative** - rend les DLLs accessibles globalement.

#### Windows 10/11:

1. Ouvrir **Paramètres système avancés**
   - Rechercher "variables d'environnement"
2. Cliquer sur **Variables d'environnement**
3. Dans **Variables système**, trouver `Path`
4. Cliquer **Modifier**
5. Ajouter: `C:\msys64\mingw64\bin`
6. **Redémarrer** l'ordinateur

**Avantage**: Les DLLs sont toujours trouvées  
**Inconvénient**: Moins portable (ne fonctionne que sur votre PC)

---

## 🔨 Compilation du projet

### Makefile (Ma configuration)

Voici le `Makefile` que j'utilise:

```makefile
# Compilateur
CXX = g++

# Flags de compilation
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O3 -I. -Iinclude

# Flags de linkage SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Windows: supprimer la console
ifeq ($(OS),Windows_NT)
    LDFLAGS += -mwindows
endif

# Exécutable
TARGET = GameOfLife.exe

# Sources
SOURCES = main.cpp Grid.cpp GameEngine.cpp EnhancedGUIRenderer.cpp \
          Config.cpp src/PatternDetector.cpp src/UIButton.cpp

# Objets
OBJECTS = $(SOURCES:.cpp=.o)

# Cible par défaut
all: $(TARGET)

# Linkage
$(TARGET): $(OBJECTS)
	@echo "🔗 Linking..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "✅ Build successful!"

# Compilation
%.o: %.cpp
	@echo "⚙️  Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	del /Q *.o $(TARGET) 2>nul || true

# Lancer
run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run
```

### Compilation étape par étape

```bash
# 1. Compiler
mingw32-make

# 2. Copier les DLLs (une seule fois)
# Méthode manuelle:
copy C:\msys64\mingw64\bin\libsfml-graphics-3.dll .
copy C:\msys64\mingw64\bin\libsfml-window-3.dll .
copy C:\msys64\mingw64\bin\libsfml-system-3.dll .
copy C:\msys64\mingw64\bin\libgcc_s_seh-1.dll .
copy C:\msys64\mingw64\bin\libstdc++-6.dll .
copy C:\msys64\mingw64\bin\libwinpthread-1.dll .

# 3. Lancer
.\GameOfLife.exe
```

---

## 🐛 Résolution de problèmes

### Problème 1: "sfml-graphics-3.dll introuvable"

**Symptôme**: Le programme se lance puis se ferme immédiatement.

**Solutions**:
1. ✅ **Vérifier que les DLLs sont à côté du .exe**
   ```powershell
   ls *.dll
   # Doit afficher les 6 DLLs SFML et GCC
   ```

2. ✅ **Utiliser Dependency Walker** pour diagnostiquer:
   - Télécharger: https://www.dependencywalker.com/
   - Ouvrir `GameOfLife.exe`
   - Voir quelles DLLs manquent (en rouge)

3. ✅ **Vérifier l'architecture** (64-bit vs 32-bit):
   ```bash
   file GameOfLife.exe
   # Doit afficher: PE32+ executable (64-bit)
   ```

---

### Problème 2: "Undefined reference to sf::..."

**Symptôme**: Erreur de compilation/linkage.

**Solutions**:
1. ✅ **Vérifier l'ordre des flags de linkage**:
   ```makefile
   # CORRECT:
   g++ main.o Grid.o -o GameOfLife.exe -lsfml-graphics -lsfml-window -lsfml-system
   
   # INCORRECT:
   g++ -lsfml-graphics main.o Grid.o -o GameOfLife.exe
   ```

2. ✅ **Vérifier les chemins d'include**:
   ```bash
   g++ -I/path/to/sfml/include ...
   ```

---

### Problème 3: Font "arial.ttf" introuvable

**Symptôme**: Écran noir ou crash au démarrage.

**Solution** (dans `EnhancedGUIRenderer.cpp`):
```cpp
// Essayer d'abord la police système Windows
if (!font_.openFromFile("C:/Windows/Fonts/arial.ttf")) {
    // Fallback: police locale
    font_.openFromFile("arial.ttf");
}
```

Ou copier `arial.ttf` à côté de l'exécutable:
```powershell
copy C:\Windows\Fonts\arial.ttf .\bin\
```

---

### Problème 4: "Cannot open include file 'SFML/Graphics.hpp'"

**Symptôme**: Erreur de compilation.

**Solutions**:
1. ✅ **Vérifier l'installation SFML**:
   ```bash
   ls C:\msys64\mingw64\include\SFML\
   # Doit afficher Graphics.hpp, Window.hpp, etc.
   ```

2. ✅ **Ajouter le chemin d'include**:
   ```makefile
   CXXFLAGS += -IC:/msys64/mingw64/include
   ```

---

## 📝 Checklist finale

Avant de distribuer votre programme:

- [ ] ✅ Toutes les DLLs SFML copiées (3 fichiers)
- [ ] ✅ Toutes les DLLs GCC Runtime copiées (3 fichiers)
- [ ] ✅ Police `arial.ttf` copiée (ou chemin absolu dans le code)
- [ ] ✅ Testé sur un autre PC (sans MSYS2 installé)
- [ ] ✅ Créer un installateur avec Inno Setup (optionnel)

---

## 🎯 Résumé - Ce que j'ai fait

Pour mon projet Game of Life:

1. ✅ **Installé MSYS2** et SFML 3.0 via `pacman`
2. ✅ **Identifié les 6 DLLs nécessaires**:
   - 3 DLLs SFML (graphics, window, system)
   - 3 DLLs GCC Runtime (gcc, stdc++, winpthread)
3. ✅ **Copié toutes les DLLs** dans le dossier `/bin` à côté de l'exécutable
4. ✅ **Configuré le Makefile** avec les flags de linkage corrects
5. ✅ **Testé sur plusieurs PCs** pour vérifier la portabilité
6. ✅ **Créé un installateur Inno Setup** qui inclut toutes les DLLs

**Résultat**: Un exécutable 100% portable qui fonctionne sur n'importe quel PC Windows 10/11 (64-bit) sans installation de SFML!

---

## 🔗 Liens utiles

- **SFML 3.0 Documentation**: https://www.sfml-dev.org/documentation/3.0.0/
- **MSYS2 Site officiel**: https://www.msys2.org/
- **Dependency Walker**: https://www.dependencywalker.com/
- **Inno Setup**: https://jrsoftware.org/isinfo.php

---

## 📧 Support

Si vous rencontrez des problèmes, consultez:
- La documentation SFML
- Les forums SFML: https://en.sfml-dev.org/forums/
- GitHub Issues de ce projet

---

**Version**: 1.1.0  
**Date**: Décembre 2025  
**Auteur**: [Votre Nom]  
**Testé sur**: Windows 10/11 (64-bit), MSYS2, SFML 3.0

---

## 🇬🇧 English Version

### Quick Setup Guide

#### 1. Install MSYS2
```bash
# Download from https://www.msys2.org/
# Install to C:\msys64

# Update MSYS2
pacman -Syu
pacman -Su
```

#### 2. Install SFML 3.0
```bash
# Install GCC compiler
pacman -S mingw-w64-x86_64-gcc

# Install Make
pacman -S mingw-w64-x86_64-make

# Install SFML
pacman -S mingw-w64-x86_64-sfml
```

#### 3. Copy Required DLLs

From `C:\msys64\mingw64\bin\` to your project's `/bin` folder:

**SFML DLLs:**
- `libsfml-graphics-3.dll`
- `libsfml-window-3.dll`
- `libsfml-system-3.dll`

**GCC Runtime DLLs:**
- `libgcc_s_seh-1.dll`
- `libstdc++-6.dll`
- `libwinpthread-1.dll`

#### 4. Compile
```bash
mingw32-make
.\GameOfLife.exe
```

#### 5. Verify DLL Dependencies

Use **Dependency Walker** to check if all DLLs are found:
- Download: https://www.dependencywalker.com/
- Open your `.exe`
- All dependencies should be green ✅

---

### Common Issues

**"DLL not found"**: Copy DLLs next to `.exe`  
**"undefined reference"**: Fix linker flag order  
**Black screen**: Check font file path (`arial.ttf`)  
**Won't compile**: Verify SFML headers in `C:\msys64\mingw64\include\SFML\`

---

**That's it! Your Game of Life should now run perfectly with SFML 3.0!** 🎮
