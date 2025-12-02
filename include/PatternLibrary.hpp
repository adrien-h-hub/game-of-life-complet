#pragma once
#include "Grid.hpp"
#include <map>
#include <string>
#include <vector>

/**
 * @class PatternLibrary
 * @brief Manages a collection of Game of Life patterns
 * 
 * Provides functionality to store, retrieve, and insert classic Game of Life patterns
 * into a grid. Supports custom pattern creation and saving.
 */
class PatternLibrary {
public:
    /**
     * @struct Pattern
     * @brief Represents a Game of Life pattern
     */
    struct Pattern {
        std::string name;
        std::vector<std::vector<bool>> cells;
        int width;
        int height;
        std::string description;
    };
    
    PatternLibrary();
    
    // Pattern retrieval
    Pattern getPattern(const std::string& name) const;
    std::vector<std::string> getPatternNames() const;
    bool hasPattern(const std::string& name) const;
    
    // Pattern insertion
    void insertPattern(Grid& grid, const std::string& name, 
                      int row, int col, bool toroidal = false) const;
    
    // Custom pattern management
    void savePattern(const std::string& name, const std::string& description,
                    const Grid& grid, int startRow, int startCol, 
                    int endRow, int endCol);
    
    void removePattern(const std::string& name);
    
private:
    std::map<std::string, Pattern> patterns_;
    void initializePatterns();
    void addPattern(const std::string& key, const std::string& name,
                   const std::string& description,
                   const std::vector<std::vector<bool>>& cells);
};
