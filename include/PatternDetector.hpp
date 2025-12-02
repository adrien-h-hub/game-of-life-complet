#pragma once
#include "Grid.hpp"
#include <string>
#include <vector>
#include <map>

/**
 * @class PatternDetector
 * @brief Detects stable patterns, oscillators, and other interesting behaviors
 */
class PatternDetector {
public:
    enum class PatternType {
        UNKNOWN,
        STILL_LIFE,      // Never changes (block, beehive, etc.)
        OSCILLATOR,      // Repeating pattern (blinker, toad, etc.)
        SPACESHIP,       // Moving pattern
        GROWING,         // Population increasing
        SHRINKING,       // Population decreasing
        EXTINCT          // All cells dead
    };
    
    PatternDetector();
    
    // Update with new grid state
    void update(const Grid& grid, int generation);
    
    // Get current pattern type
    PatternType getPatternType() const { return currentPattern_; }
    std::string getPatternName() const;
    std::string getPatternDescription() const;
    
    // Get oscillator period (if detected)
    int getOscillatorPeriod() const { return oscillatorPeriod_; }
    
    // Get statistics
    bool isStable() const;
    int getStableGenerations() const { return stableGenerations_; }
    
    void reset();
    
private:
    PatternType currentPattern_;
    int oscillatorPeriod_;
    int stableGenerations_;
    
    std::vector<std::string> gridHistory_;
    std::map<std::string, int> gridStates_;
    
    int lastPopulation_;
    int samePopulationCount_;
    
    std::string gridToString(const Grid& grid) const;
    void detectPattern();
};
