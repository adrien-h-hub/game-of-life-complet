#include "GameEngine.hpp"

GameEngine::GameEngine(const Grid& initialGrid, bool toroidal)
    : initialGrid_(std::make_unique<Grid>(initialGrid)),
      currentGrid_(std::make_unique<Grid>(initialGrid)),
      previousGrid_(std::make_unique<Grid>(initialGrid.getRows(), initialGrid.getCols())),
      generation_(0),
      toroidal_(toroidal),
      isStable_(false) {
}

void GameEngine::step() {
    *previousGrid_ = *currentGrid_;
    auto nextGrid = computeNextGeneration();
    
    if (*nextGrid == *currentGrid_) {
        isStable_ = true;
    } else {
        isStable_ = false;
    }
    
    currentGrid_ = std::move(nextGrid);
    ++generation_;
}

void GameEngine::reset() {
    *currentGrid_ = *initialGrid_;
    *previousGrid_ = Grid(initialGrid_->getRows(), initialGrid_->getCols());
    generation_ = 0;
    isStable_ = false;
}

void GameEngine::setCurrentGrid(const Grid& grid) {
    if (grid.getRows() != currentGrid_->getRows() || 
        grid.getCols() != currentGrid_->getCols()) {
        throw std::invalid_argument("Grid dimensions must match");
    }
    *currentGrid_ = grid;
}

std::unique_ptr<Grid> GameEngine::computeNextGeneration() const {
    int rows = currentGrid_->getRows();
    int cols = currentGrid_->getCols();
    auto nextGrid = std::make_unique<Grid>(rows, cols);
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int neighbors = currentGrid_->countNeighbors(row, col, toroidal_);
            bool isAlive = currentGrid_->getCell(row, col);
            
            bool willBeAlive = false;
            if (isAlive) {
                willBeAlive = (neighbors == 2 || neighbors == 3);
            } else {
                willBeAlive = (neighbors == 3);
            }
            
            nextGrid->setCell(row, col, willBeAlive);
        }
    }
    
    return nextGrid;
}
