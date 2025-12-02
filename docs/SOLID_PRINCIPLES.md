# SOLID Principles - Conway's Game of Life

## 📐 Application des Principes SOLID / SOLID Principles Application

Ce document démontre comment le projet respecte chacun des 5 principes SOLID.  
This document demonstrates how the project respects each of the 5 SOLID principles.

---

## 1️⃣ Single Responsibility Principle (SRP)

**Principe** : Une classe ne doit avoir qu'une seule raison de changer.  
**Principle**: A class should have only one reason to change.

### ✅ Application dans le projet / Application in the Project

#### Classe `Grid`
**Responsabilité unique** : Gérer les données de la grille cellulaire  
**Single responsibility**: Manage cellular grid data

```cpp
class Grid {
private:
    std::vector<std::vector<bool>> cells_;
    int rows_, cols_;
    
public:
    // Uniquement la gestion des cellules
    // Only cell management
    bool getCell(int row, int col) const;
    void setCell(int row, int col, bool alive);
    void clear();
    int countNeighbors(int row, int col) const;
};
```

**Ce que Grid NE fait PAS** :
- ❌ Affichage graphique
- ❌ Application des règles du jeu
- ❌ Gestion des événements utilisateur

**What Grid does NOT do**:
- ❌ Graphical display
- ❌ Apply game rules
- ❌ User event handling

#### Classe `GameEngine`
**Responsabilité unique** : Appliquer les règles de Conway  
**Single responsibility**: Apply Conway's rules

```cpp
class GameEngine {
public:
    void step();              // Avance d'une génération
    void reset();             // Réinitialise
    int getGeneration() const;
    
private:
    void applyRules();        // Applique règles de Conway
};
```

**Ce que GameEngine NE fait PAS** :
- ❌ Rendu graphique
- ❌ Détection de motifs
- ❌ Gestion de l'historique

#### Classe `EnhancedGUIRenderer`
**Responsabilité unique** : Affichage et interaction utilisateur  
**Single responsibility**: Display and user interaction

```cpp
class EnhancedGUIRenderer {
public:
    void run();               // Boucle principale
    
private:
    void handleEvents();      // Gestion des événements
    void render();            // Affichage
    void renderGrid();
    void renderStats();
    void renderHelp();
};
```

**Ce que Renderer NE fait PAS** :
- ❌ Calcul des règles du jeu
- ❌ Gestion des données de grille
- ❌ Détection de motifs

#### Classe `PatternDetector`
**Responsabilité unique** : Détecter les motifs stables  
**Single responsibility**: Detect stable patterns

```cpp
class PatternDetector {
public:
    void update(const Grid& grid, int generation);
    bool isStable() const;
    bool isOscillator() const;
    std::string detectKnownPattern(const Grid& grid);
};
```

### 📊 Bénéfices / Benefits

- ✅ **Maintenabilité** : Modifications localisées / Localized modifications
- ✅ **Testabilité** : Tests unitaires ciblés / Targeted unit tests
- ✅ **Lisibilité** : Code clair et focalisé / Clear and focused code
- ✅ **Réutilisabilité** : Composants indépendants / Independent components

---

## 2️⃣ Open/Closed Principle (OCP)

**Principe** : Ouvert à l'extension, fermé à la modification.  
**Principle**: Open for extension, closed for modification.

### ✅ Application : Système de Thèmes / Theme System

```cpp
enum class Theme {
    NEON,
    OCEAN,
    FOREST,
    SUNSET,
    LAVENDER,
    RAINBOW,
    FIRE,
    ICE,
    COUNT
};

struct ThemeColors {
    sf::Color background;
    sf::Color gridLines;
    sf::Color aliveCell;
    // ...
};

// Extension facile : ajouter un nouveau thème
// Easy extension: add a new theme
const ThemeColors& getThemeColors(Theme theme) {
    static std::unordered_map<Theme, ThemeColors> themes = {
        {Theme::NEON, {/* couleurs néon */}},
        {Theme::OCEAN, {/* couleurs océan */}},
        // Ajouter ici sans modifier le code existant
        // Add here without modifying existing code
    };
    return themes[theme];
}
```

**Extension sans modification** :
```cpp
// ✅ BIEN : Ajouter un nouveau thème
{Theme::GALAXY, {sf::Color(10, 10, 30), /* ... */}}

// ❌ MAL : Modifier le code existant des thèmes
// Pas besoin de toucher aux autres thèmes !
```

### ✅ Application : Détecteurs de Motifs / Pattern Detectors

```cpp
class PatternDetector {
protected:
    virtual bool matchPattern(const Grid& grid) = 0;
    
public:
    void update(const Grid& grid, int generation) {
        if (matchPattern(grid)) {
            // Déclencher action
        }
    }
};

// Extension : nouveau détecteur
class GliderDetector : public PatternDetector {
protected:
    bool matchPattern(const Grid& grid) override {
        // Logique spécifique au glider
        return detectGlider(grid);
    }
};

// Aucune modification du code de base nécessaire !
```

### 📊 Bénéfices / Benefits

- ✅ **Extensibilité** : Nouvelles fonctionnalités sans risque
- ✅ **Stabilité** : Code existant non modifié
- ✅ **Évolutivité** : Système évolutif

---

## 3️⃣ Liskov Substitution Principle (LSP)

**Principe** : Les sous-types doivent être substituables à leurs types de base.  
**Principle**: Subtypes must be substitutable for their base types.

### ✅ Application : Grilles Interchangeables / Interchangeable Grids

```cpp
class GridBase {
public:
    virtual bool getCell(int row, int col) const = 0;
    virtual void setCell(int row, int col, bool alive) = 0;
    virtual int countNeighbors(int row, int col) const = 0;
    virtual ~GridBase() = default;
};

class Grid : public GridBase {
    // Implémentation standard
};

class WrapAroundGrid : public GridBase {
    // Implémentation avec bords qui se rejoignent
    // Implementation with wrapping edges
    int countNeighbors(int row, int col) const override {
        // Les bords se connectent (topologie toroïdale)
        // Edges connect (toroidal topology)
    }
};

// Utilisation : n'importe quelle grille fonctionne
// Usage: any grid works
void processGrid(GridBase& grid) {
    int neighbors = grid.countNeighbors(5, 5);
    // Fonctionne avec Grid OU WrapAroundGrid
    // Works with Grid OR WrapAroundGrid
}
```

### ✅ Respect du contrat / Contract Compliance

**Contrat de base** :
```cpp
// Préconditions
assert(row >= 0 && row < rows);
assert(col >= 0 && col < cols);

// Postconditions
bool alive = getCell(row, col);
assert(alive == true || alive == false);  // Valeur booléenne valide
```

**Sous-classe respecte le contrat** :
```cpp
class ToroidalGrid : public GridBase {
    bool getCell(int row, int col) const override {
        // Normalise les coordonnées, mais respecte le contrat
        row = (row % rows_ + rows_) % rows_;
        col = (col % cols_ + cols_) % cols_;
        return cells_[row][col];  // Toujours bool
    }
};
```

### 📊 Bénéfices / Benefits

- ✅ **Polymorphisme sûr** : Substitution sans surprise
- ✅ **Fiabilité** : Comportement prévisible
- ✅ **Flexibilité** : Implémentations variées possibles

---

## 4️⃣ Interface Segregation Principle (ISP)

**Principe** : Les clients ne doivent pas dépendre d'interfaces qu'ils n'utilisent pas.  
**Principle**: Clients should not depend on interfaces they don't use.

### ✅ Application : Interfaces Minimales / Minimal Interfaces

#### Interface de Lecture Seule / Read-Only Interface

```cpp
class IReadableGrid {
public:
    virtual bool getCell(int row, int col) const = 0;
    virtual int countNeighbors(int row, int col) const = 0;
    virtual int getRows() const = 0;
    virtual int getCols() const = 0;
    virtual ~IReadableGrid() = default;
};

class IWritableGrid {
public:
    virtual void setCell(int row, int col, bool alive) = 0;
    virtual void clear() = 0;
    virtual ~IWritableGrid() = default;
};

// Grid implémente les deux interfaces
class Grid : public IReadableGrid, public IWritableGrid {
    // Implémentation complète
};
```

**Utilisation ciblée** :
```cpp
// Le renderer n'a besoin que de lire
class Renderer {
    void draw(const IReadableGrid& grid) {
        // Accès lecture seule, pas de modification possible
        bool cell = grid.getCell(0, 0);
        // grid.setCell(0, 0, true);  // ❌ Erreur de compilation !
    }
};

// L'éditeur a besoin d'écrire
class Editor {
    void edit(IWritableGrid& grid) {
        grid.setCell(5, 5, true);  // ✅ Modification autorisée
    }
};
```

### ✅ Application : Statistiques / Statistics

```cpp
// Interface minimale pour les stats
class IStatisticsProvider {
public:
    virtual int getGeneration() const = 0;
    virtual int getPopulation() const = 0;
    virtual ~IStatisticsProvider() = default;
};

// Le panneau de stats n'a besoin que de ces infos
class StatsPanel {
    void display(const IStatisticsProvider& provider) {
        int gen = provider.getGeneration();
        int pop = provider.getPopulation();
        // Pas besoin de connaître le moteur complet
    }
};
```

### 📊 Bénéfices / Benefits

- ✅ **Couplage faible** : Dépendances minimales
- ✅ **Sécurité** : Accès restreint approprié
- ✅ **Clarté** : Intentions explicites

---

## 5️⃣ Dependency Inversion Principle (DIP)

**Principe** : Dépendre d'abstractions, pas de concrétions.  
**Principle**: Depend on abstractions, not concretions.

### ✅ Application : Injection de Dépendances / Dependency Injection

```cpp
// ❌ MAUVAIS : Dépendance directe sur implémentation concrète
class BadRenderer {
    Grid grid_;  // Dépendance concrète
    
public:
    BadRenderer() : grid_(100, 100) {}  // Création interne
};

// ✅ BON : Dépendance sur abstraction
class GoodRenderer {
    IReadableGrid& grid_;  // Dépendance abstraite
    
public:
    // Injection de dépendance via constructeur
    GoodRenderer(IReadableGrid& grid) : grid_(grid) {}
};
```

### ✅ Application : GameEngine & Renderer

```cpp
// Abstraction
class IGameLogic {
public:
    virtual void step() = 0;
    virtual const IReadableGrid& getCurrentGrid() const = 0;
    virtual int getGeneration() const = 0;
    virtual ~IGameLogic() = default;
};

// Implémentation concrète
class GameEngine : public IGameLogic {
    // Détails d'implémentation
};

// Renderer dépend de l'abstraction
class EnhancedGUIRenderer {
    IGameLogic& logic_;  // Dépendance sur interface
    
public:
    EnhancedGUIRenderer(IGameLogic& logic) : logic_(logic) {}
    
    void render() {
        const IReadableGrid& grid = logic_.getCurrentGrid();
        // Fonctionne avec n'importe quelle implémentation de IGameLogic
    }
};

// Utilisation : injection
int main() {
    GameEngine engine(200, 200);
    EnhancedGUIRenderer renderer(engine);  // Injection
    renderer.run();
}
```

### ✅ Configuration Externe / External Configuration

```cpp
// Interface de configuration
class IConfig {
public:
    virtual int getGridRows() const = 0;
    virtual int getGridCols() const = 0;
    virtual Theme getInitialTheme() const = 0;
    virtual ~IConfig() = default;
};

// Classes dépendent de IConfig, pas de Config concrète
class Application {
    IConfig& config_;
    
public:
    Application(IConfig& config) : config_(config) {
        // Utilise l'abstraction
        int rows = config_.getRows();
    }
};
```

### 📊 Bénéfices / Benefits

- ✅ **Testabilité** : Injection de mocks facile
- ✅ **Flexibilité** : Implémentations interchangeables
- ✅ **Découplage** : Modules indépendants
- ✅ **Maintenabilité** : Modifications localisées

---

## 🎯 Résumé de l'Application / Application Summary

| Principe | Application | Impact |
|----------|-------------|--------|
| **SRP** | Classes à responsabilité unique (Grid, Engine, Renderer) | Code modulaire et maintenable |
| **OCP** | Système de thèmes extensible, détecteurs de motifs | Évolution sans modification |
| **LSP** | Grilles substituables, interfaces cohérentes | Polymorphisme fiable |
| **ISP** | Interfaces minimales (lecture/écriture séparées) | Couplage minimal |
| **DIP** | Injection de dépendances, abstractions | Testabilité et flexibilité |

---

## 📈 Métriques de Qualité / Quality Metrics

### Couplage (Coupling)
- **Low coupling** entre modules ✅
- Dépendances via interfaces ✅
- Pas de dépendances circulaires ✅

### Cohésion (Cohesion)
- **High cohesion** dans chaque classe ✅
- Responsabilités claires ✅
- Fonctions liées regroupées ✅

### Complexité (Complexity)
- Classes simples et focalisées ✅
- Méthodes courtes (<50 lignes) ✅
- Logique claire et lisible ✅

---

## 🧪 Testabilité / Testability

Grâce aux principes SOLID, le code est hautement testable :

```cpp
// Test unitaire de Grid (SRP)
TEST(GridTest, CountNeighbors) {
    Grid grid(10, 10);
    grid.setCell(5, 5, true);
    EXPECT_EQ(grid.countNeighbors(4, 4), 1);
}

// Test avec mock (DIP)
class MockGameLogic : public IGameLogic {
    // Implémentation de test
};

TEST(RendererTest, DisplaysCorrectly) {
    MockGameLogic mockLogic;
    EnhancedGUIRenderer renderer(mockLogic);
    // Test du renderer sans vraie logique de jeu
}
```

---

## 📚 Références / References

- **Clean Code** by Robert C. Martin
- **SOLID Principles** - Wikipedia
- **Design Patterns** by Gang of Four

---

**Conclusion** : Ce projet démontre une application rigoureuse des principes SOLID, résultant en un code maintenable, extensible, et testable.

**Conclusion**: This project demonstrates rigorous application of SOLID principles, resulting in maintainable, extensible, and testable code.

---

**Date**: December 1, 2025  
**Version**: 1.1.0  
**Author**: [Your Name]
