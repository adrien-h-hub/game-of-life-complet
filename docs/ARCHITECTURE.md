# Architecture - Conway's Game of Life v1.1.0

## 📐 System Overview

This document describes the complete architecture of the Game of Life Enhanced Edition, explaining design decisions, component interactions, and implementation details.

## 🏗️ High-Level Architecture

```
┌─────────────────────────────────────────────────────────┐
│                     User Interface Layer                 │
│  ┌─────────────────────────────────────────────────┐   │
│  │         EnhancedGUIRenderer (SFML)              │   │
│  │  • Event Handling                                │   │
│  │  • Visual Rendering                              │   │
│  │  • Theme Management                              │   │
│  │  • UI Overlays                                   │   │
│  └─────────────────────────────────────────────────┘   │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│                   Game Logic Layer                       │
│  ┌──────────────┐  ┌──────────────┐  ┌───────────────┐│
│  │  GameEngine  │  │PatternDetector│ │TimelineManager││
│  │              │  │               │  │               ││
│  │ • Rules      │  │ • Detection   │  │ • History     ││
│  │ • State Mgmt │  │ • Hashing     │  │ • Undo/Redo   ││
│  └──────────────┘  └──────────────┘  └───────────────┘│
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│                    Data Layer                            │
│  ┌──────────────┐  ┌──────────────┐  ┌───────────────┐│
│  │     Grid     │  │ Statistics   │  │PatternLibrary ││
│  │              │  │              │  │               ││
│  │ • Cell Data  │  │ • Metrics    │  │ • Known Patterns│
│  │ • Neighbors  │  │ • Tracking   │  │ • Templates   ││
│  └──────────────┘  └──────────────┘  └───────────────┘│
└─────────────────────────────────────────────────────────┘
```

## 🔧 Component Details

### 1. Grid Class

**Responsibility**: Manage the 2D cellular grid and cell states

```cpp
class Grid {
private:
    std::vector<std::vector<bool>> cells_;
    int rows_, cols_;
    
public:
    Grid(int rows, int cols);
    
    // Core operations
    bool getCell(int row, int col) const;
    void setCell(int row, int col, bool alive);
    void clear();
    
    // Analysis
    int countNeighbors(int row, int col) const;
    int countAliveCells() const;
    
    // Comparison
    bool operator==(const Grid& other) const;
    size_t hash() const;
};
```

**Design Decisions**:
- Uses `std::vector<std::vector<bool>>` for simplicity and cache locality
- Bounds checking for safety
- Efficient neighbor counting with 8-direction iteration
- Hash function for pattern detection

### 2. GameEngine Class

**Responsibility**: Apply Conway's rules and manage game state

```cpp
class GameEngine {
private:
    Grid* currentGrid_;
    Grid* previousGrid_;
    Grid* initialGrid_;
    int generation_;
    bool isStable_;
    
public:
    GameEngine(int rows, int cols);
    
    // Simulation
    void step();                    // Advance one generation
    void reset();                   // Reset to initial state
    void resetGeneration();         // Reset counter to 0
    
    // State queries
    int getGeneration() const;
    bool isStable() const;
    const Grid& getCurrentGrid() const;
    Grid& getCurrentGridMutable();
    
private:
    void applyRules();              // Apply Conway's rules
    bool checkStability();          // Check if stable
};
```

**Conway's Rules Implementation**:
```cpp
void GameEngine::applyRules() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int neighbors = currentGrid_->countNeighbors(row, col);
            bool alive = currentGrid_->getCell(row, col);
            
            // Rule 1: Birth
            if (!alive && neighbors == 3) {
                previousGrid_->setCell(row, col, true);
            }
            // Rule 2: Survival
            else if (alive && (neighbors == 2 || neighbors == 3)) {
                previousGrid_->setCell(row, col, true);
            }
            // Rule 3: Death
            else {
                previousGrid_->setCell(row, col, false);
            }
        }
    }
    
    std::swap(currentGrid_, previousGrid_);
    generation_++;
}
```

### 3. EnhancedGUIRenderer Class

**Responsibility**: Handle all visualization and user interaction

```cpp
class EnhancedGUIRenderer {
private:
    sf::RenderWindow& window_;
    GameEngine& engine_;
    sf::Font font_;
    
    // Visual state
    Theme currentTheme_;
    bool showGrid_, showStats_, showMiniMap_, showHelp_;
    bool showCellAge_;
    
    // Camera
    sf::View gameView_, uiView_;
    sf::Vector2f panOffset_;
    float zoomLevel_;
    
    // History
    std::deque<Grid> history_;
    int maxHistorySize_;
    
    // Pattern detection
    PatternDetector patternDetector_;
    bool autoPauseOnStable_;
    int stableGenerations_;
    
public:
    EnhancedGUIRenderer(GameEngine& engine, const Config& config);
    
    void run();                     // Main loop
    
private:
    void handleEvents();            // Input processing
    void update(float deltaTime);   // Logic update
    void render();                  // Draw everything
    
    // Event handlers
    void handleKeyPress(sf::Keyboard::Key key);
    void handleMouseButton(sf::Mouse::Button button, sf::Vector2i pos);
    void handleMouseWheel(float delta);
    
    // Rendering methods
    void renderGrid();
    void renderStats();
    void renderMiniMap();
    void renderHelp();
    void renderCellAges();
    
    // History management
    void addToHistory();
    void undo();
    void redo();
};
```

**Theme System**:
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
    sf::Color deadCell;
    sf::Color panelBg;
    sf::Color text;
};

const ThemeColors& getThemeColors(Theme theme);
```

### 4. PatternDetector Class

**Responsibility**: Detect known patterns and oscillators

```cpp
class PatternDetector {
private:
    std::deque<size_t> stateHistory_;
    int maxHistorySize_;
    PatternLibrary& library_;
    
public:
    PatternDetector(PatternLibrary& lib, int historySize = 10);
    
    void update(const Grid& grid, int generation);
    void reset();
    
    bool isStable() const;          // No change
    bool isOscillator() const;      // Periodic
    int getOscillatorPeriod() const;
    
    std::string detectKnownPattern(const Grid& grid);
};
```

**State Hashing**:
```cpp
size_t Grid::hash() const {
    size_t h = 0;
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {
            if (cells_[r][c]) {
                h ^= std::hash<int>{}(r * cols_ + c);
            }
        }
    }
    return h;
}
```

### 5. TimelineManager Class

**Responsibility**: Manage generation history for time travel

```cpp
class TimelineManager {
private:
    std::deque<Grid> timeline_;
    int currentIndex_;
    int maxSize_;
    
public:
    TimelineManager(int maxSize = 100);
    
    void push(const Grid& grid);
    bool canUndo() const;
    bool canRedo() const;
    
    const Grid& undo();
    const Grid& redo();
    void clear();
};
```

## 🔄 Data Flow

### 1. Normal Simulation Step

```
User presses SPACE
    ↓
EnhancedGUIRenderer::handleKeyPress()
    ↓
isPaused_ = false
    ↓
EnhancedGUIRenderer::update()
    ↓
GameEngine::step()
    ↓
applyRules() → Apply Conway's rules
    ↓
generation_++
    ↓
PatternDetector::update()
    ↓
Check if stable → Auto-pause if needed
    ↓
addToHistory() → Save to timeline
    ↓
EnhancedGUIRenderer::render()
    ↓
Display updated grid
```

### 2. Time Travel (Rewind)

```
User presses ← (LEFT)
    ↓
EnhancedGUIRenderer::handleKeyPress()
    ↓
undo()
    ↓
TimelineManager::undo()
    ↓
Retrieve previous Grid
    ↓
engine_.setCurrentGrid()
    ↓
engine_.resetGeneration() → Gen = 0
    ↓
Render previous state
```

### 3. Random Pattern Generation

```
User presses R
    ↓
EnhancedGUIRenderer::handleKeyPress()
    ↓
grid.clear()
    ↓
Generate 3×3 random pattern
    ↓
4-9 cells alive (random)
    ↓
Center on grid
    ↓
engine_.resetGeneration() → Gen = 0
    ↓
Reset camera position (-243px)
    ↓
addToHistory()
    ↓
Render new pattern
```

## 🎨 Rendering Pipeline

```
EnhancedGUIRenderer::render()
    ↓
┌─────────────────────────────────┐
│ 1. Set Game View (with camera)  │
│    • Apply pan offset           │
│    • Apply zoom level           │
└─────────────────────────────────┘
    ↓
┌─────────────────────────────────┐
│ 2. Render Grid                  │
│    • Draw cells                 │
│    • Apply theme colors         │
│    • Show age if enabled        │
│    • Draw grid lines            │
└─────────────────────────────────┘
    ↓
┌─────────────────────────────────┐
│ 3. Set UI View (fixed)          │
│    • Reset to window coords     │
└─────────────────────────────────┘
    ↓
┌─────────────────────────────────┐
│ 4. Render UI Overlays           │
│    • Stats panel (if enabled)   │
│    • Mini-map (if enabled)      │
│    • Help overlay (if enabled)  │
└─────────────────────────────────┘
    ↓
window_.display()
```

## 🧩 Design Patterns Used

### 1. **Strategy Pattern** (Theme System)
- Multiple theme strategies
- Easy to add new themes
- Runtime theme switching

### 2. **Observer Pattern** (Event Handling)
- SFML event system
- Key press, mouse, window events
- Decoupled event handling

### 3. **Command Pattern** (History/Undo)
- Each generation is a "command"
- Timeline stores command history
- Undo/redo functionality

### 4. **State Pattern** (Game States)
- Playing, Paused, Recording
- Clean state transitions
- State-specific behavior

### 5. **Singleton Pattern** (Config)
- Global configuration access
- Single source of truth
- Lazy initialization

## 📊 Performance Considerations

### Memory Management
- **Grid**: ~200x200 cells = 40KB per grid
- **History**: Max 100 grids = ~4MB
- **Total**: ~5-10MB typical usage

### Rendering Optimization
- Only redraw when changed
- Batch rendering with vertex arrays
- Cull off-screen cells
- VSync to prevent tearing

### Computation Optimization
- Neighbor counting: O(1) per cell
- Grid update: O(rows × cols)
- Pattern detection: O(history_size)
- Hash computation: O(alive_cells)

## 🔒 Thread Safety

**Current Implementation**: Single-threaded
- SFML rendering in main thread
- Game logic in main thread
- No race conditions

**Future Consideration**: Multi-threading
- Background pattern detection
- Parallel cell updates
- Render thread separation

## 📝 Configuration System

```cpp
struct Config {
    // Grid
    int gridRows = 200;
    int gridCols = 200;
    float cellSize = 4.0f;
    
    // Window
    int windowWidth = 1280;
    int windowHeight = 720;
    bool fullscreen = false;
    
    // Simulation
    float initialSpeed = 100.0f;  // ms per generation
    bool showGrid = true;
    Theme initialTheme = Theme::NEON;
    
    // History
    int maxHistorySize = 100;
    
    // Pattern Detection
    bool autoPause = true;
    int stableThreshold = 3;
};
```

## 🔗 Dependencies

```
GameOfLife
├── SFML 3.0
│   ├── Graphics
│   ├── Window
│   └── System
├── C++ Standard Library
│   ├── <vector>
│   ├── <deque>
│   ├── <string>
│   ├── <unordered_map>
│   └── <algorithm>
└── System
    └── OpenGL 3.3+ (via SFML)
```

## 🎯 SOLID Principles Application

### Single Responsibility Principle
- **Grid**: Only manages cell data
- **GameEngine**: Only applies rules
- **Renderer**: Only handles display
- **PatternDetector**: Only detects patterns

### Open/Closed Principle
- Easy to add new themes without modifying existing code
- New pattern detectors can be added via inheritance
- Extensible configuration system

### Liskov Substitution Principle
- All Grid types are interchangeable
- Pattern detectors follow common interface

### Interface Segregation Principle
- Minimal, focused interfaces
- No bloated classes with unused methods

### Dependency Inversion Principle
- High-level modules don't depend on low-level
- Both depend on abstractions (interfaces)

---

## 📚 Related Documentation

- [SOLID_PRINCIPLES.md](SOLID_PRINCIPLES.md) - Detailed SOLID analysis
- [USER_GUIDE_EN.md](USER_GUIDE_EN.md) - User guide (English)
- [USER_GUIDE_FR.md](USER_GUIDE_FR.md) - User guide (French)
- [BUILDING.md](BUILDING.md) - Build instructions

---

**Last Updated**: December 1, 2025  
**Version**: 1.1.0  
**Author**: [Your Name]
