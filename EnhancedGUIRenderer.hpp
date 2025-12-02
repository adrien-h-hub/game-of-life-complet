#ifndef ENHANCED_GUI_RENDERER_HPP
#define ENHANCED_GUI_RENDERER_HPP

#include "GameEngine.hpp"
#include "Config.hpp"
#include "UIButton.hpp"
#include "PatternDetector.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <deque>

class EnhancedGUIRenderer {
public:
    enum class Theme {
        CLASSIC, NEON, OCEAN, FIRE, MATRIX, PASTEL, MIDNIGHT, SUNSET
    };
    
    struct Statistics {
        int generation;
        int population;
        int births;
        int deaths;
        int maxPopulation;
        int minPopulation;
        float averagePopulation;
        std::deque<int> populationHistory;
        
        Statistics() : generation(0), population(0), births(0), deaths(0),
                      maxPopulation(0), minPopulation(999999), averagePopulation(0.0f) {}
    };
    
    EnhancedGUIRenderer(GameEngine& engine, const Config& config);
    ~EnhancedGUIRenderer();
    void run();

private:
    GameEngine& engine_;
    sf::RenderWindow window_;
    sf::Font font_;
    sf::View gameView_;
    sf::View uiView_;
    sf::Vector2f panOffset_;
    float zoomLevel_;
    float targetZoom_;
    
    sf::Clock clock_;
    sf::Clock fpsCounter_;
    float timeSinceLastStep_;
    int stepMs_;
    bool isPaused_;
    float animationTime_;
    int fps_;
    int frameCount_;
    
    int cellSize_;
    bool showGrid_;
    bool showHelp_;
    bool showStats_;
    bool showMiniMap_;
    bool showCellAge_;
    Theme currentTheme_;
    
    std::vector<std::vector<int>> cellAges_;
    int maxCellAge_;
    
    sf::Vector2i lastMousePos_;
    bool isPanning_;
    bool isDrawing_;
    bool isErasing_;
    
    sf::VertexArray cellVertices_;
    Statistics stats_;
    std::deque<Grid> history_;
    int historyIndex_;
    const int maxHistorySize_ = 50;
    
    bool isRecording_;
    std::vector<Grid> recording_;
    bool isPlayingBack_;
    int playbackIndex_;
    
    // Beautiful UI Components
    std::vector<std::unique_ptr<UIButton>> buttons_;
    UIPanel controlPanel_;
    UIPanel infoPanel_;
    PatternDetector patternDetector_;
    bool showUI_;
    sf::Vector2i mousePos_;
    bool autoPauseOnStable_;
    int stableDetectionCount_;
    bool wasStableLastFrame_;
    
    void handleEvents();
    void handleKeyPress(sf::Keyboard::Key key);
    void handleCellClick(int mouseX, int mouseY);
    void handleMouseDrag(int mouseX, int mouseY);
    void handleZoom(float delta);
    
    void update(float deltaTime);
    void updateStatistics();
    void updateCellAges();
    void smoothZoom(float deltaTime);
    
    void renderFrame();
    void buildVertexArrays();
    void renderCells();
    void renderGrid();
    void renderHelp();
    void renderStats();
    void renderMiniMap();
    void renderGraph();
    void renderModernUI();
    void renderControlPanel();
    void renderPatternInfo();
    void initializeButtons();
    void handleButtonClick(int mouseX, int mouseY);
    
    sf::Vector2i screenToGrid(int screenX, int screenY) const;
    sf::Color getThemeColor(float intensity, float age = 0.0f) const;
    void addToHistory();
    void undo();
    void redo();
    void cycleTheme();
    void randomFill(float density);
    void invertGrid();
};

#endif
