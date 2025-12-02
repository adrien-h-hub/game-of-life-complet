#include "PatternLibrary.hpp"
#include <algorithm>

PatternLibrary::PatternLibrary() {
    initializePatterns();
}

void PatternLibrary::addPattern(const std::string& key, const std::string& name,
                                const std::string& description,
                                const std::vector<std::vector<bool>>& cells) {
    Pattern pattern;
    pattern.name = name;
    pattern.description = description;
    pattern.cells = cells;
    pattern.height = cells.size();
    pattern.width = cells.empty() ? 0 : cells[0].size();
    patterns_[key] = pattern;
}

void PatternLibrary::initializePatterns() {
    // 1. Glider - Classic spaceship
    addPattern("glider", "Glider", "Classic spaceship that travels diagonally",
        {{0, 1, 0},
         {0, 0, 1},
         {1, 1, 1}});
    
    // 2. Blinker - Simple oscillator
    addPattern("blinker", "Blinker", "Period-2 oscillator, simplest pattern",
        {{1, 1, 1}});
    
    // 3. Block - Still life
    addPattern("block", "Block", "Stable 2x2 block, never changes",
        {{1, 1},
         {1, 1}});
    
    // 4. Toad - Oscillator
    addPattern("toad", "Toad", "Period-2 oscillator",
        {{0, 1, 1, 1},
         {1, 1, 1, 0}});
    
    // 5. Beacon - Oscillator
    addPattern("beacon", "Beacon", "Period-2 oscillator with blinking corners",
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 1, 1},
         {0, 0, 1, 1}});
    
    // 6. Pulsar - Large oscillator
    addPattern("pulsar", "Pulsar", "Period-3 oscillator with beautiful symmetry",
        {{0,0,1,1,1,0,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,0},
         {1,0,0,0,0,1,0,1,0,0,0,0,1},
         {1,0,0,0,0,1,0,1,0,0,0,0,1},
         {1,0,0,0,0,1,0,1,0,0,0,0,1},
         {0,0,1,1,1,0,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,1,1,1,0,0,0,1,1,1,0,0},
         {1,0,0,0,0,1,0,1,0,0,0,0,1},
         {1,0,0,0,0,1,0,1,0,0,0,0,1},
         {1,0,0,0,0,1,0,1,0,0,0,0,1},
         {0,0,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,1,1,1,0,0,0,1,1,1,0,0}});
    
    // 7. Lightweight Spaceship (LWSS)
    addPattern("lwss", "Lightweight Spaceship", "Faster spaceship, travels horizontally",
        {{0, 1, 0, 0, 1},
         {1, 0, 0, 0, 0},
         {1, 0, 0, 0, 1},
         {1, 1, 1, 1, 0}});
    
    // 8. R-pentomino - Methuselah
    addPattern("rpentomino", "R-pentomino", "Chaotic pattern that stabilizes after 1103 generations",
        {{0, 1, 1},
         {1, 1, 0},
         {0, 1, 0}});
    
    // 9. Acorn - Methuselah
    addPattern("acorn", "Acorn", "Tiny pattern that runs for 5206 generations",
        {{0, 1, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 0, 0},
         {1, 1, 0, 0, 1, 1, 1}});
    
    // 10. Gosper Glider Gun
    addPattern("gun", "Gosper Glider Gun", "Creates gliders infinitely",
        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
         {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
         {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
         {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}});
}

PatternLibrary::Pattern PatternLibrary::getPattern(const std::string& name) const {
    auto it = patterns_.find(name);
    if (it != patterns_.end()) {
        return it->second;
    }
    return Pattern(); // Return empty pattern if not found
}

std::vector<std::string> PatternLibrary::getPatternNames() const {
    std::vector<std::string> names;
    for (const auto& pair : patterns_) {
        names.push_back(pair.first);
    }
    std::sort(names.begin(), names.end());
    return names;
}

bool PatternLibrary::hasPattern(const std::string& name) const {
    return patterns_.find(name) != patterns_.end();
}

void PatternLibrary::insertPattern(Grid& grid, const std::string& name,
                                   int row, int col, bool toroidal) const {
    auto it = patterns_.find(name);
    if (it == patterns_.end()) return;
    
    const Pattern& pattern = it->second;
    
    for (int r = 0; r < pattern.height; ++r) {
        for (int c = 0; c < pattern.width; ++c) {
            int targetRow = row + r;
            int targetCol = col + c;
            
            if (toroidal) {
                targetRow = (targetRow % grid.getRows() + grid.getRows()) % grid.getRows();
                targetCol = (targetCol % grid.getCols() + grid.getCols()) % grid.getCols();
            }
            
            if (targetRow >= 0 && targetRow < grid.getRows() &&
                targetCol >= 0 && targetCol < grid.getCols()) {
                grid.setCell(targetRow, targetCol, pattern.cells[r][c]);
            }
        }
    }
}

void PatternLibrary::savePattern(const std::string& name, const std::string& description,
                                 const Grid& grid, int startRow, int startCol,
                                 int endRow, int endCol) {
    if (startRow > endRow || startCol > endCol) return;
    if (startRow < 0 || endRow >= grid.getRows()) return;
    if (startCol < 0 || endCol >= grid.getCols()) return;
    
    int height = endRow - startRow + 1;
    int width = endCol - startCol + 1;
    
    std::vector<std::vector<bool>> cells(height, std::vector<bool>(width));
    
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            cells[r][c] = grid.getCell(startRow + r, startCol + c);
        }
    }
    
    addPattern(name, name, description, cells);
}

void PatternLibrary::removePattern(const std::string& name) {
    patterns_.erase(name);
}
