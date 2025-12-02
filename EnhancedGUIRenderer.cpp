#include "EnhancedGUIRenderer.hpp"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>

EnhancedGUIRenderer::EnhancedGUIRenderer(GameEngine& engine, const Config& config)
    : engine_(engine),
      window_(sf::VideoMode(sf::Vector2u(1280, 800)), "Conway's Game of Life - Enhanced Edition", sf::Style::Default),
      zoomLevel_(1.0f),
      targetZoom_(1.0f),
      timeSinceLastStep_(0.0f),
      stepMs_(config.getStepMs()),
      isPaused_(true),
      animationTime_(0.0f),
      fps_(60),
      frameCount_(0),
      cellSize_(config.getCellSize()),
      showGrid_(config.showGrid()),
      showHelp_(false),
      showStats_(true),
      showMiniMap_(true),
      showCellAge_(false),
      currentTheme_(Theme::NEON),
      maxCellAge_(0),
      isPanning_(false),
      isDrawing_(false),
      isErasing_(false),
      historyIndex_(-1),
      isRecording_(false),
      isPlayingBack_(false),
      playbackIndex_(0),
      controlPanel_(20, 690, 400, 90, ""),
      infoPanel_(1050, 20, 210, 200, ""),
      showUI_(true),
      autoPauseOnStable_(true),
      stableDetectionCount_(0),
      wasStableLastFrame_(false) {
    
    window_.setFramerateLimit(60);
    
    // Load font
    if (!font_.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        // Try alternative
        font_.openFromFile("arial.ttf");
    }
    
    // Initialize views
    gameView_ = window_.getDefaultView();
    uiView_ = window_.getDefaultView();
    
    // Shift view to the left to reduce empty space on right
    panOffset_.x = -243.0f;  // Move left by 243 pixels
    gameView_.setCenter(sf::Vector2f(
        static_cast<float>(window_.getSize().x) / 2.0f + panOffset_.x,
        static_cast<float>(window_.getSize().y) / 2.0f
    ));
    
    // Initialize cell ages
    const Grid& grid = engine_.getCurrentGrid();
    cellAges_.resize(grid.getRows(), std::vector<int>(grid.getCols(), 0));
    
    // Initialize vertex array
    cellVertices_.setPrimitiveType(sf::PrimitiveType::Triangles);
    
    // Set panel titles after construction
    controlPanel_.setTitle("Controls");
    infoPanel_.setTitle("Pattern Info");
    
    // Initialize beautiful UI buttons
    initializeButtons();
    
    addToHistory();
}

EnhancedGUIRenderer::~EnhancedGUIRenderer() {
}

void EnhancedGUIRenderer::run() {
    while (window_.isOpen()) {
        handleEvents();
        
        float deltaTime = clock_.restart().asSeconds();
        update(deltaTime);
        
        renderFrame();
        
        frameCount_++;
        if (fpsCounter_.getElapsedTime().asSeconds() >= 1.0f) {
            fps_ = frameCount_;
            frameCount_ = 0;
            fpsCounter_.restart();
        }
    }
}

void EnhancedGUIRenderer::handleEvents() {
    while (const auto event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handleKeyPress(keyPressed->code);
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            // Track mouse position for button hover effects
            mousePos_ = mouseMoved->position;
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                // Check if clicking on a button first
                handleButtonClick(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                
                // If not on button, handle cell click
                isDrawing_ = true;
                handleCellClick(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
            }
            else if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                isPanning_ = true;
                lastMousePos_ = mouseButtonPressed->position;
            }
            else if (mouseButtonPressed->button == sf::Mouse::Button::Middle) {
                isErasing_ = true;
            }
        }
        else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
                isDrawing_ = false;
            }
            else if (mouseButtonReleased->button == sf::Mouse::Button::Right) {
                isPanning_ = false;
            }
            else if (mouseButtonReleased->button == sf::Mouse::Button::Middle) {
                isErasing_ = false;
            }
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            if (isPanning_) {
                sf::Vector2i delta = mouseMoved->position - lastMousePos_;
                panOffset_.x -= delta.x / zoomLevel_;
                panOffset_.y -= delta.y / zoomLevel_;
                lastMousePos_ = mouseMoved->position;
            }
            else if (isDrawing_ || isErasing_) {
                handleMouseDrag(mouseMoved->position.x, mouseMoved->position.y);
            }
        }
        else if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
            handleZoom(mouseWheelScrolled->delta);
        }
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            gameView_.setSize(sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)));
            uiView_.setSize(sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)));
        }
    }
}

void EnhancedGUIRenderer::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::Space:
            isPaused_ = !isPaused_;
            break;
        case sf::Keyboard::Key::N:
            if (isPaused_) {
                engine_.step();
                updateStatistics();
                updateCellAges();
                addToHistory();
            }
            break;
        case sf::Keyboard::Key::R:
            // Generate RANDOM 3x3 pattern in the CENTER!
            {
                Grid& grid = engine_.getCurrentGridMutable();
                grid.clear();  // Clear everything first
                
                int centerRow = grid.getRows() / 2;
                int centerCol = grid.getCols() / 2;
                
                // Create 3x3 pattern with at least 7 cells alive
                std::vector<std::pair<int, int>> cells;
                for (int r = -1; r <= 1; r++) {
                    for (int c = -1; c <= 1; c++) {
                        cells.push_back({r, c});
                    }
                }
                
                // Shuffle and pick 4-9 cells to be alive
                std::random_shuffle(cells.begin(), cells.end());
                int aliveCount = 4 + (rand() % 6);  // 4, 5, 6, 7, 8, or 9 cells alive
                
                for (size_t i = 0; i < cells.size(); i++) {
                    int r = cells[i].first;
                    int c = cells[i].second;
                    int row = centerRow + r;
                    int col = centerCol + c;
                    
                    if (row >= 0 && row < grid.getRows() && 
                        col >= 0 && col < grid.getCols()) {
                        bool alive = (i < (size_t)aliveCount);  // First 7-9 are alive
                        grid.setCell(row, col, alive);
                    }
                }
                
                // RESET GENERATION TO 0 and keep optimized view position!
                engine_.resetGeneration();
                
                // Keep camera at optimized position (243px left)
                panOffset_.x = -243.0f;
                panOffset_.y = 0.0f;
                zoomLevel_ = 1.0f;
                gameView_.setCenter(sf::Vector2f(
                    static_cast<float>(window_.getSize().x) / 2.0f + panOffset_.x,
                    static_cast<float>(window_.getSize().y) / 2.0f
                ));
                
                stats_ = Statistics();
                cellAges_.clear();
                cellAges_.resize(grid.getRows(), 
                               std::vector<int>(grid.getCols(), 0));
                patternDetector_.reset();
                addToHistory();
            }
            break;
        case sf::Keyboard::Key::C:
            engine_.getCurrentGridMutable().clear();
            updateCellAges();
            addToHistory();
            break;
        case sf::Keyboard::Key::G:
            showGrid_ = !showGrid_;
            break;
        case sf::Keyboard::Key::H:
            showHelp_ = !showHelp_;
            break;
        case sf::Keyboard::Key::S:
            // Save current state to file (exam requirement)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                // Ctrl+S: Save state
                {
                    std::string filename = "saved_state_gen" + std::to_string(engine_.getGeneration()) + ".txt";
                    if (engine_.getCurrentGrid().saveToFile(filename)) {
                        std::cout << "State saved to: " << filename << std::endl;
                    }
                }
            } else {
                // S alone: Toggle stats (keep existing functionality)
                showStats_ = !showStats_;
            }
            break;
        case sf::Keyboard::Key::M:
            showMiniMap_ = !showMiniMap_;
            break;
        case sf::Keyboard::Key::A:
            showCellAge_ = !showCellAge_;
            break;
        case sf::Keyboard::Key::K:
            cycleTheme();
            break;
        case sf::Keyboard::Key::T:
            engine_.setToroidal(!engine_.isToroidal());
            break;
        case sf::Keyboard::Key::F:
            randomFill(0.3f);
            addToHistory();
            break;
        case sf::Keyboard::Key::I:
            invertGrid();
            addToHistory();
            break;
        case sf::Keyboard::Key::P:
            if (!isRecording_) {
                isRecording_ = true;
                recording_.clear();
            } else {
                isRecording_ = false;
            }
            break;
        case sf::Keyboard::Key::B:
            if (!recording_.empty()) {
                isPlayingBack_ = !isPlayingBack_;
                playbackIndex_ = 0;
            }
            break;
        case sf::Keyboard::Key::Add:
        case sf::Keyboard::Key::Equal:
            stepMs_ = std::max(10, stepMs_ - 50);
            break;
        case sf::Keyboard::Key::Subtract:
        case sf::Keyboard::Key::Hyphen:
            stepMs_ = std::min(2000, stepMs_ + 50);
            break;
        case sf::Keyboard::Key::Z:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                undo();
            }
            break;
        case sf::Keyboard::Key::Y:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                redo();
            }
            break;
        case sf::Keyboard::Key::Left:
            // REWIND - Go back one step and reset generation to 0
            undo();
            engine_.resetGeneration();
            break;
        case sf::Keyboard::Key::Right:
            // FORWARD - Go forward one step and reset generation to 0
            redo();
            engine_.resetGeneration();
            break;
        case sf::Keyboard::Key::O:
            // Toggle auto-pause on stable patterns (O for "on/off auto-pause")
            autoPauseOnStable_ = !autoPauseOnStable_;
            break;
        case sf::Keyboard::Key::Escape:
            window_.close();
            break;
        default:
            break;
    }
}

void EnhancedGUIRenderer::handleCellClick(int mouseX, int mouseY) {
    sf::Vector2i gridPos = screenToGrid(mouseX, mouseY);
    const Grid& grid = engine_.getCurrentGrid();
    
    if (gridPos.x >= 0 && gridPos.x < grid.getCols() && 
        gridPos.y >= 0 && gridPos.y < grid.getRows()) {
        if (isErasing_) {
            engine_.getCurrentGridMutable().setCell(gridPos.y, gridPos.x, false);
        } else {
            engine_.getCurrentGridMutable().toggleCell(gridPos.y, gridPos.x);
        }
        addToHistory();
    }
}

void EnhancedGUIRenderer::handleMouseDrag(int mouseX, int mouseY) {
    sf::Vector2i gridPos = screenToGrid(mouseX, mouseY);
    const Grid& grid = engine_.getCurrentGrid();
    
    if (gridPos.x >= 0 && gridPos.x < grid.getCols() && 
        gridPos.y >= 0 && gridPos.y < grid.getRows()) {
        if (isErasing_) {
            engine_.getCurrentGridMutable().setCell(gridPos.y, gridPos.x, false);
        } else {
            engine_.getCurrentGridMutable().setCell(gridPos.y, gridPos.x, true);
        }
    }
}

void EnhancedGUIRenderer::handleZoom(float delta) {
    if (delta > 0) {
        targetZoom_ = std::min(3.0f, targetZoom_ * 1.1f);
    } else {
        targetZoom_ = std::max(0.3f, targetZoom_ * 0.9f);
    }
}

void EnhancedGUIRenderer::update(float deltaTime) {
    animationTime_ += deltaTime;
    
    // Smooth zoom
    smoothZoom(deltaTime);
    
    // Update game
    if (!isPaused_ && !isPlayingBack_) {
        timeSinceLastStep_ += deltaTime * 1000.0f;
        if (timeSinceLastStep_ >= stepMs_) {
            engine_.step();
            updateStatistics();
            updateCellAges();
            
            // Update pattern detector to detect oscillators!
            patternDetector_.update(engine_.getCurrentGrid(), engine_.getGeneration());
            
            // AUTO-PAUSE when pattern becomes stable!
            if (autoPauseOnStable_ && patternDetector_.isStable()) {
                stableDetectionCount_++;
                // Pause after confirming stable for 3 generations
                if (stableDetectionCount_ >= 3 && !wasStableLastFrame_) {
                    isPaused_ = true;
                    wasStableLastFrame_ = true;
                    // Visual/audio feedback could go here
                }
            } else {
                stableDetectionCount_ = 0;
                wasStableLastFrame_ = false;
            }
            
            if (isRecording_) {
                recording_.push_back(engine_.getCurrentGrid());
            }
            timeSinceLastStep_ = 0.0f;
        }
    }
    
    // Playback
    if (isPlayingBack_ && !recording_.empty()) {
        timeSinceLastStep_ += deltaTime * 1000.0f;
        if (timeSinceLastStep_ >= stepMs_) {
            if (playbackIndex_ < recording_.size()) {
                engine_.setCurrentGrid(recording_[playbackIndex_]);
                playbackIndex_++;
            } else {
                isPlayingBack_ = false;
                playbackIndex_ = 0;
            }
            timeSinceLastStep_ = 0.0f;
        }
    }
}

void EnhancedGUIRenderer::updateStatistics() {
    const Grid& grid = engine_.getCurrentGrid();
    int newPop = grid.countLiving();
    
    stats_.births = std::max(0, newPop - stats_.population);
    stats_.deaths = std::max(0, stats_.population - newPop);
    stats_.population = newPop;
    stats_.generation = engine_.getGeneration();
    
    stats_.maxPopulation = std::max(stats_.maxPopulation, stats_.population);
    if (stats_.population > 0) {
        stats_.minPopulation = std::min(stats_.minPopulation, stats_.population);
    }
    
    stats_.populationHistory.push_back(stats_.population);
    if (stats_.populationHistory.size() > 200) {
        stats_.populationHistory.pop_front();
    }
    
    if (stats_.generation > 0) {
        float sum = 0;
        for (int pop : stats_.populationHistory) {
            sum += pop;
        }
        stats_.averagePopulation = sum / stats_.populationHistory.size();
    }
}

void EnhancedGUIRenderer::updateCellAges() {
    const Grid& grid = engine_.getCurrentGrid();
    maxCellAge_ = 0;
    
    for (int row = 0; row < grid.getRows(); ++row) {
        for (int col = 0; col < grid.getCols(); ++col) {
            if (grid.getCell(row, col)) {
                cellAges_[row][col]++;
                maxCellAge_ = std::max(maxCellAge_, cellAges_[row][col]);
            } else {
                cellAges_[row][col] = 0;
            }
        }
    }
}

void EnhancedGUIRenderer::smoothZoom(float deltaTime) {
    float zoomSpeed = 5.0f;
    zoomLevel_ += (targetZoom_ - zoomLevel_) * zoomSpeed * deltaTime;
    
    gameView_.setSize(sf::Vector2f(static_cast<float>(window_.getSize().x) / zoomLevel_, static_cast<float>(window_.getSize().y) / zoomLevel_));
    gameView_.setCenter(sf::Vector2f(static_cast<float>(window_.getSize().x) / (2.0f * zoomLevel_) + panOffset_.x,
                        static_cast<float>(window_.getSize().y) / (2.0f * zoomLevel_) + panOffset_.y));
}

void EnhancedGUIRenderer::renderFrame() {
    window_.clear(sf::Color(15, 15, 25));
    
    // Render game view
    window_.setView(gameView_);
    renderCells();
    if (showGrid_ && zoomLevel_ > 0.5f) {
        renderGrid();
    }
    
    // Render UI view
    window_.setView(uiView_);
    if (showStats_) renderStats();
    if (showMiniMap_) renderMiniMap();
    if (showHelp_) renderHelp();
    
    // Render beautiful modern UI with interactive buttons!
    // TODO: Debug UI crash
    // renderModernUI();
    
    window_.display();
}

void EnhancedGUIRenderer::buildVertexArrays() {
    const Grid& grid = engine_.getCurrentGrid();
    cellVertices_.clear();
    
    // Add optimization: only render visible cells
    sf::FloatRect visibleArea(sf::Vector2f(panOffset_.x, panOffset_.y), 
                             sf::Vector2f(static_cast<float>(window_.getSize().x) / zoomLevel_, 
                             static_cast<float>(window_.getSize().y) / zoomLevel_));
    
    for (int row = 0; row < grid.getRows(); ++row) {
        for (int col = 0; col < grid.getCols(); ++col) {
            if (!grid.getCell(row, col)) continue;
            
            float x = col * cellSize_;
            float y = row * cellSize_;
            
            // Culling
            if (x + cellSize_ < visibleArea.position.x || x > visibleArea.position.x + visibleArea.size.x ||
                y + cellSize_ < visibleArea.position.y || y > visibleArea.position.y + visibleArea.size.y) {
                continue;
            }
            
            float ageNormalized = maxCellAge_ > 0 ? (float)cellAges_[row][col] / maxCellAge_ : 0.0f;
            float pulse = 0.85f + 0.15f * std::sin(animationTime_ * 3.0f + row * 0.1f + col * 0.1f);
            
            sf::Color color = getThemeColor(pulse, showCellAge_ ? ageNormalized : 0.0f);
            
            // Two triangles to form a square (SFML 3.0 uses Triangles instead of Quads)
            // Triangle 1
            cellVertices_.append(sf::Vertex(sf::Vector2f(x, y), color));
            cellVertices_.append(sf::Vertex(sf::Vector2f(x + cellSize_, y), color));
            cellVertices_.append(sf::Vertex(sf::Vector2f(x, y + cellSize_), color));
            // Triangle 2
            cellVertices_.append(sf::Vertex(sf::Vector2f(x + cellSize_, y), color));
            cellVertices_.append(sf::Vertex(sf::Vector2f(x + cellSize_, y + cellSize_), color));
            cellVertices_.append(sf::Vertex(sf::Vector2f(x, y + cellSize_), color));
        }
    }
}

void EnhancedGUIRenderer::renderCells() {
    buildVertexArrays();
    window_.draw(cellVertices_);
}

void EnhancedGUIRenderer::renderGrid() {
    const Grid& grid = engine_.getCurrentGrid();
    sf::Color gridColor(50, 50, 70, 100);
    
    for (int row = 0; row <= grid.getRows(); ++row) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, row * cellSize_), gridColor),
            sf::Vertex(sf::Vector2f(grid.getCols() * cellSize_, row * cellSize_), gridColor)
        };
        window_.draw(line, 2, sf::PrimitiveType::Lines);
    }
    
    for (int col = 0; col <= grid.getCols(); ++col) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(col * cellSize_, 0), gridColor),
            sf::Vertex(sf::Vector2f(col * cellSize_, grid.getRows() * cellSize_), gridColor)
        };
        window_.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void EnhancedGUIRenderer::renderHelp() {
    sf::RectangleShape panel(sf::Vector2f(400, 500));
    panel.setPosition(sf::Vector2f(static_cast<float>(window_.getSize().x) / 2 - 200, static_cast<float>(window_.getSize().y) / 2 - 250));
    panel.setFillColor(sf::Color(20, 20, 35, 240));
    panel.setOutlineColor(sf::Color(100, 100, 150, 200));
    panel.setOutlineThickness(2);
    window_.draw(panel);
    
    std::vector<std::string> helpText = {
        "CONTROLS",
        "",
        "SPACE - Play/Pause",
        "N - Next generation",
        "R - Random 3x3 center",
        "C - Clear",
        "",
        "LEFT ARROW - Rewind (go back)",
        "RIGHT ARROW - Forward (redo)",
        "O - Auto-pause on stable",
        "",
        "K - Cycle themes",
        "A - Toggle cell age",
        "G - Toggle grid",
        "S - Toggle stats",
        "M - Toggle mini-map",
        "H - Toggle help",
        "",
        "F - Random fill",
        "I - Invert",
        "",
        "+/- Speed",
        "Ctrl+Z - Undo",
        "Ctrl+Y - Redo",
        "",
        "Left Click - Draw",
        "Right Drag - Pan",
        "Scroll - Zoom",
        "",
        "ESC - Exit"
    };
    
    float y = panel.getPosition().y + 20;
    for (const auto& line : helpText) {
        sf::Text text(font_, line, line == "CONTROLS" ? 20 : 14);
        text.setPosition(sf::Vector2f(panel.getPosition().x + 20, y));
        text.setFillColor(line == "CONTROLS" ? sf::Color(100, 200, 255) : sf::Color::White);
        window_.draw(text);
        y += line == "CONTROLS" ? 30 : (line.empty() ? 10 : 20);
    }
}

void EnhancedGUIRenderer::renderStats() {
    sf::RectangleShape panel(sf::Vector2f(280, 350));
    panel.setPosition(sf::Vector2f(10, 10));
    panel.setFillColor(sf::Color(20, 20, 35, 220));
    panel.setOutlineColor(sf::Color(100, 100, 150, 150));
    panel.setOutlineThickness(2);
    window_.draw(panel);
    
    std::string patternStatus = "";
    if (patternDetector_.isStable()) {
        patternStatus = "STABLE: " + patternDetector_.getPatternName();
    }
    
    std::vector<std::string> lines = {
        "STATISTICS",
        "",
        "Generation: " + std::to_string(stats_.generation),
        "Population: " + std::to_string(stats_.population),
        "Births: " + std::to_string(stats_.births),
        "Deaths: " + std::to_string(stats_.deaths),
        "Max Pop: " + std::to_string(stats_.maxPopulation),
        "Min Pop: " + std::to_string(stats_.minPopulation),
        "Avg Pop: " + std::to_string((int)stats_.averagePopulation),
        "",
        "FPS: " + std::to_string(fps_),
        "Speed: " + std::to_string(1000 / stepMs_) + " gen/s",
        "",
        patternStatus,
        autoPauseOnStable_ ? "Auto-pause: ON" : "Auto-pause: OFF",
        "Zoom: " + std::to_string((int)(zoomLevel_ * 100)) + "%",
        "",
        "Status: " + std::string(isPaused_ ? "PAUSED" : "RUNNING"),
        "Recording: " + std::string(isRecording_ ? "ON" : "OFF"),
        "Theme: " + std::to_string((int)currentTheme_)
    };
    
    float y = 30;
    for (size_t i = 0; i < lines.size(); ++i) {
        sf::Text text(font_, lines[i], i == 0 ? 18 : 13);
        text.setPosition(sf::Vector2f(25, y));
        text.setFillColor(i == 0 ? sf::Color(100, 200, 255) : sf::Color::White);
        window_.draw(text);
        y += i == 0 ? 35 : (lines[i].empty() ? 8 : 20);
    }
    
    // Draw graph
    renderGraph();
}

void EnhancedGUIRenderer::renderGraph() {
    if (stats_.populationHistory.size() < 2) return;
    
    sf::RectangleShape graphBg(sf::Vector2f(250, 80));
    graphBg.setPosition(sf::Vector2f(20, 270));
    graphBg.setFillColor(sf::Color(10, 10, 20, 180));
    window_.draw(graphBg);
    
    int maxPop = stats_.maxPopulation > 0 ? stats_.maxPopulation : 1;
    float graphWidth = 250;
    float graphHeight = 80;
    float xStep = graphWidth / std::min(200.0f, (float)stats_.populationHistory.size());
    
    for (size_t i = 1; i < stats_.populationHistory.size(); ++i) {
        float x1 = 20 + (i - 1) * xStep;
        float y1 = 270 + graphHeight - (stats_.populationHistory[i - 1] / (float)maxPop * graphHeight);
        float x2 = 20 + i * xStep;
        float y2 = 270 + graphHeight - (stats_.populationHistory[i] / (float)maxPop * graphHeight);
        
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x1, y1), sf::Color(0, 255, 150)),
            sf::Vertex(sf::Vector2f(x2, y2), sf::Color(0, 255, 150))
        };
        window_.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void EnhancedGUIRenderer::renderMiniMap() {
    const Grid& grid = engine_.getCurrentGrid();
    float miniSize = 150;
    sf::RectangleShape bg(sf::Vector2f(miniSize + 10, miniSize + 10));
    bg.setPosition(sf::Vector2f(static_cast<float>(window_.getSize().x) - miniSize - 20, static_cast<float>(window_.getSize().y) - miniSize - 20));
    bg.setFillColor(sf::Color(20, 20, 35, 220));
    bg.setOutlineColor(sf::Color(100, 100, 150, 150));
    bg.setOutlineThickness(2);
    window_.draw(bg);
    
    float cellW = miniSize / grid.getCols();
    float cellH = miniSize / grid.getRows();
    
    for (int row = 0; row < grid.getRows(); ++row) {
        for (int col = 0; col < grid.getCols(); ++col) {
            if (grid.getCell(row, col)) {
                sf::RectangleShape cell(sf::Vector2f(cellW, cellH));
                cell.setPosition(sf::Vector2f(static_cast<float>(window_.getSize().x) - miniSize - 15 + col * cellW, static_cast<float>(window_.getSize().y) - miniSize - 15 + row * cellH));
                cell.setFillColor(sf::Color::White);
                window_.draw(cell);
            }
        }
    }
}

sf::Vector2i EnhancedGUIRenderer::screenToGrid(int screenX, int screenY) const {
    sf::Vector2f worldPos = window_.mapPixelToCoords(sf::Vector2i(screenX, screenY), gameView_);
    return sf::Vector2i(worldPos.x / cellSize_, worldPos.y / cellSize_);
}

sf::Color EnhancedGUIRenderer::getThemeColor(float intensity, float age) const {
    sf::Color baseColor;
    sf::Color ageColor;
    
    switch (currentTheme_) {
        case Theme::NEON:
            baseColor = sf::Color(0, 255, 255);
            ageColor = sf::Color(255, 0, 255);
            break;
        case Theme::OCEAN:
            baseColor = sf::Color(100, 200, 255);
            ageColor = sf::Color(0, 100, 200);
            break;
        case Theme::FIRE:
            baseColor = sf::Color(255, 255, 0);
            ageColor = sf::Color(255, 50, 0);
            break;
        case Theme::MATRIX:
            baseColor = sf::Color(0, 255, 0);
            ageColor = sf::Color(0, 150, 0);
            break;
        case Theme::PASTEL:
            baseColor = sf::Color(255, 182, 193);
            ageColor = sf::Color(221, 160, 221);
            break;
        case Theme::MIDNIGHT:
            baseColor = sf::Color(135, 206, 250);
            ageColor = sf::Color(25, 25, 112);
            break;
        case Theme::SUNSET:
            baseColor = sf::Color(255, 165, 0);
            ageColor = sf::Color(138, 43, 226);
            break;
        case Theme::CLASSIC:
        default:
            return sf::Color(255 * intensity, 255 * intensity, 255 * intensity);
    }
    
    sf::Color result;
    result.r = baseColor.r * (1 - age) + ageColor.r * age;
    result.g = baseColor.g * (1 - age) + ageColor.g * age;
    result.b = baseColor.b * (1 - age) + ageColor.b * age;
    result.r *= intensity;
    result.g *= intensity;
    result.b *= intensity;
    
    return result;
}

void EnhancedGUIRenderer::addToHistory() {
    // Remove any redo history
    while (historyIndex_ < (int)history_.size() - 1) {
        history_.pop_back();
    }
    
    history_.push_back(engine_.getCurrentGrid());
    
    if (history_.size() > maxHistorySize_) {
        history_.pop_front();
    } else {
        historyIndex_++;
    }
}

void EnhancedGUIRenderer::undo() {
    if (historyIndex_ > 0) {
        historyIndex_--;
        engine_.setCurrentGrid(history_[historyIndex_]);
    }
}

void EnhancedGUIRenderer::redo() {
    if (historyIndex_ < (int)history_.size() - 1) {
        historyIndex_++;
        engine_.setCurrentGrid(history_[historyIndex_]);
    }
}

void EnhancedGUIRenderer::cycleTheme() {
    int themeInt = (int)currentTheme_;
    themeInt = (themeInt + 1) % 8;
    currentTheme_ = (Theme)themeInt;
}

void EnhancedGUIRenderer::randomFill(float density) {
    Grid& grid = engine_.getCurrentGridMutable();
    for (int row = 0; row < grid.getRows(); ++row) {
        for (int col = 0; col < grid.getCols(); ++col) {
            bool alive = (rand() / (float)RAND_MAX) < density;
            grid.setCell(row, col, alive);
        }
    }
}

void EnhancedGUIRenderer::invertGrid() {
    Grid& grid = engine_.getCurrentGridMutable();
    for (int row = 0; row < grid.getRows(); ++row) {
        for (int col = 0; col < grid.getCols(); ++col) {
            grid.toggleCell(row, col);
        }
    }
}

// ============================================================================
// BEAUTIFUL MODERN UI IMPLEMENTATION
// ============================================================================

void EnhancedGUIRenderer::initializeButtons() {
    float buttonY = 730;
    float buttonX = 40;
    float buttonWidth = 80;
    float buttonHeight = 35;
    float spacing = 10;
    
    // Play/Pause button (PRIMARY style - most important!)
    auto playBtn = std::make_unique<UIButton>("PLAY", buttonX, buttonY, buttonWidth, buttonHeight, UIButton::Style::PRIMARY);
    playBtn->setCallback([this]() {
        isPaused_ = !isPaused_;
        if (!isPaused_ && !buttons_.empty()) {
            buttons_[0]->setText("PAUSE");
        } else if (!buttons_.empty()) {
            buttons_[0]->setText("PLAY");
        }
    });
    buttons_.push_back(std::move(playBtn));
    buttonX += buttonWidth + spacing;
    
    // Step button (SECONDARY)
    auto stepBtn = std::make_unique<UIButton>("STEP", buttonX, buttonY, buttonWidth, buttonHeight, UIButton::Style::SECONDARY);
    stepBtn->setCallback([this]() {
        if (isPaused_) {
            engine_.step();
            updateCellAges();
            updateStatistics();
            patternDetector_.update(engine_.getCurrentGrid(), engine_.getGeneration());
        }
    });
    buttons_.push_back(std::move(stepBtn));
    buttonX += buttonWidth + spacing;
    
    // Reset button (INFO)
    auto resetBtn = std::make_unique<UIButton>("RESET", buttonX, buttonY, buttonWidth, buttonHeight, UIButton::Style::INFO);
    resetBtn->setCallback([this]() {
        if (historyIndex_ >= 0 && historyIndex_ < static_cast<int>(history_.size())) {
            engine_.setCurrentGrid(history_[0]);
            historyIndex_ = 0;
            patternDetector_.reset();
        }
    });
    buttons_.push_back(std::move(resetBtn));
    buttonX += buttonWidth + spacing;
    
    // Clear button (DANGER)
    auto clearBtn = std::make_unique<UIButton>("CLEAR", buttonX, buttonY, buttonWidth, buttonHeight, UIButton::Style::DANGER);
    clearBtn->setCallback([this]() {
        Grid& grid = engine_.getCurrentGridMutable();
        for (int r = 0; r < grid.getRows(); ++r) {
            for (int c = 0; c < grid.getCols(); ++c) {
                grid.setCell(r, c, false);
            }
        }
        patternDetector_.reset();
        addToHistory();
    });
    buttons_.push_back(std::move(clearBtn));
}

void EnhancedGUIRenderer::handleButtonClick(int mouseX, int mouseY) {
    for (auto& button : buttons_) {
        if (button->contains(mouseX, mouseY)) {
            button->handleClick();
            return;
        }
    }
}

void EnhancedGUIRenderer::renderModernUI() {
    if (!showUI_) return;
    
    window_.setView(uiView_);
    
    // Render panels with beautiful glass-morphism effect
    controlPanel_.render(window_, font_);
    infoPanel_.render(window_, font_);
    
    // Render interactive buttons with hover effects
    for (auto& button : buttons_) {
        // Check hover state
        bool isHovered = button->contains(mousePos_.x, mousePos_.y);
        button->handleHover(isHovered);
        button->render(window_, font_);
    }
    
    // Render pattern detection info
    renderPatternInfo();
}

void EnhancedGUIRenderer::renderPatternInfo() {
    if (!infoPanel_.isVisible()) return;
    
    float panelX = 1070;
    float panelY = 70;
    float lineHeight = 22;
    
    // Pattern type with beautiful icon
    std::string patternName = patternDetector_.getPatternName();
    sf::Text patternText(font_, "Pattern: ", 14);
    patternText.setPosition(sf::Vector2f(panelX, panelY));
    patternText.setFillColor(sf::Color(180, 180, 200));
    window_.draw(patternText);
    
    sf::Text patternValue(font_, patternName, 14);
    patternValue.setPosition(sf::Vector2f(panelX, panelY + lineHeight));
    
    // Color code based on pattern type
    if (patternName.find("Oscillator") != std::string::npos) {
        patternValue.setFillColor(sf::Color(100, 200, 255)); // Blue for oscillators
        patternValue.setStyle(sf::Text::Bold);
    } else if (patternName.find("Still Life") != std::string::npos) {
        patternValue.setFillColor(sf::Color(100, 255, 100)); // Green for still life
        patternValue.setStyle(sf::Text::Bold);
    } else if (patternName.find("Growing") != std::string::npos) {
        patternValue.setFillColor(sf::Color(255, 200, 100)); // Orange for growing
    } else if (patternName.find("Shrinking") != std::string::npos) {
        patternValue.setFillColor(sf::Color(255, 100, 100)); // Red for shrinking
    } else {
        patternValue.setFillColor(sf::Color(200, 200, 200)); // Gray for unknown
    }
    
    window_.draw(patternValue);
    panelY += lineHeight * 2 + 10;
    
    // Description
    std::string desc = patternDetector_.getPatternDescription();
    sf::Text descText(font_, desc, 11);
    descText.setPosition(sf::Vector2f(panelX, panelY));
    descText.setFillColor(sf::Color(150, 150, 170));
    window_.draw(descText);
    panelY += lineHeight * 2;
    
    // Oscillator period (if applicable)
    if (patternDetector_.getOscillatorPeriod() > 0) {
        sf::Text periodText(font_, "Period: " + std::to_string(patternDetector_.getOscillatorPeriod()), 13);
        periodText.setPosition(sf::Vector2f(panelX, panelY));
        periodText.setFillColor(sf::Color(255, 215, 0)); // Gold
        periodText.setStyle(sf::Text::Bold);
        window_.draw(periodText);
        panelY += lineHeight;
    }
    
    // Stability indicator
    if (patternDetector_.isStable()) {
        sf::Text stableText(font_, "✓ STABLE PATTERN", 12);
        stableText.setPosition(sf::Vector2f(panelX, panelY));
        stableText.setFillColor(sf::Color(0, 255, 128));
        stableText.setStyle(sf::Text::Bold);
        window_.draw(stableText);
    }
}
