#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Grid.hpp"
#include <memory>

class GameEngine {
public:
    explicit GameEngine(const Grid& initialGrid, bool toroidal = false);
    
    void step();
    void reset();
    void resetGeneration() { generation_ = 0; isStable_ = false; }
    const Grid& getCurrentGrid() const { return *currentGrid_; }
    Grid& getCurrentGridMutable() { return *currentGrid_; }
    const Grid& getInitialGrid() const { return *initialGrid_; }
    int getGeneration() const { return generation_; }
    bool isStable() const { return isStable_; }
    void setToroidal(bool toroidal) { toroidal_ = toroidal; }
    bool isToroidal() const { return toroidal_; }
    void setCurrentGrid(const Grid& grid);

private:
    std::unique_ptr<Grid> initialGrid_;
    std::unique_ptr<Grid> currentGrid_;
    std::unique_ptr<Grid> previousGrid_;
    int generation_;
    bool toroidal_;
    bool isStable_;
    
    std::unique_ptr<Grid> computeNextGeneration() const;
};

#endif
