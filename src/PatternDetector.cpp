#include "PatternDetector.hpp"
#include <sstream>
#include <algorithm>

PatternDetector::PatternDetector()
    : currentPattern_(PatternType::UNKNOWN),
      oscillatorPeriod_(0),
      stableGenerations_(0),
      lastPopulation_(0),
      samePopulationCount_(0) {
}

void PatternDetector::update(const Grid& grid, int generation) {
    std::string gridState = gridToString(grid);
    
    // Count current population
    int population = 0;
    for (int r = 0; r < grid.getRows(); ++r) {
        for (int c = 0; c < grid.getCols(); ++c) {
            if (grid.getCell(r, c)) population++;
        }
    }
    
    // Check for extinction
    if (population == 0) {
        currentPattern_ = PatternType::EXTINCT;
        return;
    }
    
    // Track population changes
    if (population == lastPopulation_) {
        samePopulationCount_++;
    } else {
        samePopulationCount_ = 0;
    }
    lastPopulation_ = population;
    
    // Add to history (keep last 100 states)
    gridHistory_.push_back(gridState);
    if (gridHistory_.size() > 100) {
        gridHistory_.erase(gridHistory_.begin());
    }
    
    // Check if we've seen this state before
    if (gridStates_.find(gridState) != gridStates_.end()) {
        // We found a repeating pattern!
        int lastSeen = gridStates_[gridState];
        int period = generation - lastSeen;
        
        if (period == 0 || period == 1) {
            // Still life (never changes)
            currentPattern_ = PatternType::STILL_LIFE;
            oscillatorPeriod_ = 0;
            stableGenerations_++;
        } else if (period > 1 && period <= 30) {
            // Oscillator (repeating pattern)
            currentPattern_ = PatternType::OSCILLATOR;
            oscillatorPeriod_ = period;
            stableGenerations_++;
        }
    } else {
        gridStates_[gridState] = generation;
        
        // Not repeating yet, check if growing/shrinking
        if (samePopulationCount_ < 3) {
            if (population > lastPopulation_) {
                currentPattern_ = PatternType::GROWING;
            } else if (population < lastPopulation_) {
                currentPattern_ = PatternType::SHRINKING;
            }
        }
    }
    
    // Clear old states to prevent memory issues
    if (gridStates_.size() > 1000) {
        gridStates_.clear();
    }
}

std::string PatternDetector::getPatternName() const {
    switch (currentPattern_) {
        case PatternType::STILL_LIFE:
            return "Still Life";
        case PatternType::OSCILLATOR:
            return "Oscillator (Period " + std::to_string(oscillatorPeriod_) + ")";
        case PatternType::SPACESHIP:
            return "Spaceship";
        case PatternType::GROWING:
            return "Growing";
        case PatternType::SHRINKING:
            return "Shrinking";
        case PatternType::EXTINCT:
            return "Extinct";
        default:
            return "Unknown";
    }
}

std::string PatternDetector::getPatternDescription() const {
    switch (currentPattern_) {
        case PatternType::STILL_LIFE:
            return "Pattern never changes - stable formation";
        case PatternType::OSCILLATOR:
            return "Pattern repeats every " + std::to_string(oscillatorPeriod_) + " generations";
        case PatternType::SPACESHIP:
            return "Pattern moving across grid";
        case PatternType::GROWING:
            return "Population is increasing";
        case PatternType::SHRINKING:
            return "Population is decreasing";
        case PatternType::EXTINCT:
            return "All cells are dead";
        default:
            return "Pattern behavior not yet determined";
    }
}

bool PatternDetector::isStable() const {
    return currentPattern_ == PatternType::STILL_LIFE || 
           currentPattern_ == PatternType::OSCILLATOR;
}

void PatternDetector::reset() {
    currentPattern_ = PatternType::UNKNOWN;
    oscillatorPeriod_ = 0;
    stableGenerations_ = 0;
    gridHistory_.clear();
    gridStates_.clear();
    lastPopulation_ = 0;
    samePopulationCount_ = 0;
}

std::string PatternDetector::gridToString(const Grid& grid) const {
    std::ostringstream oss;
    for (int r = 0; r < grid.getRows(); ++r) {
        for (int c = 0; c < grid.getCols(); ++c) {
            oss << (grid.getCell(r, c) ? '1' : '0');
        }
    }
    return oss.str();
}
