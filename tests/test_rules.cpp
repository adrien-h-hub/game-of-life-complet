/**
 * @file test_rules.cpp
 * @brief Unit tests for Conway's Game of Life rules using Catch2 v3
 */

#include <catch2/catch_test_macros.hpp>
#include "../Grid.hpp"
#include "../GameEngine.hpp"

TEST_CASE("Conway's Rule 1: Birth", "[rules][birth]") {
    GameEngine engine(10, 10);
    Grid& grid = engine.getCurrentGridMutable();
    
    SECTION("Dead cell with exactly 3 neighbors becomes alive") {
        // Create a configuration with a dead cell at (5,5) with 3 living neighbors
        grid.clear();
        grid.setCell(4, 4, true);  // Neighbor 1
        grid.setCell(4, 5, true);  // Neighbor 2
        grid.setCell(5, 4, true);  // Neighbor 3
        // Cell (5,5) is dead with 3 neighbors
        
        REQUIRE(grid.getCell(5, 5) == false);
        REQUIRE(grid.countNeighbors(5, 5, false) == 3);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == true);
    }
    
    SECTION("Dead cell with 2 neighbors stays dead") {
        grid.clear();
        grid.setCell(4, 4, true);
        grid.setCell(4, 5, true);
        
        REQUIRE(grid.getCell(5, 5) == false);
        REQUIRE(grid.countNeighbors(5, 5, false) == 2);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == false);
    }
    
    SECTION("Dead cell with 4 neighbors stays dead") {
        grid.clear();
        grid.setCell(4, 4, true);
        grid.setCell(4, 5, true);
        grid.setCell(5, 4, true);
        grid.setCell(6, 5, true);
        
        REQUIRE(grid.getCell(5, 5) == false);
        REQUIRE(grid.countNeighbors(5, 5, false) == 4);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == false);
    }
}

TEST_CASE("Conway's Rule 2: Survival", "[rules][survival]") {
    GameEngine engine(10, 10);
    Grid& grid = engine.getCurrentGridMutable();
    
    SECTION("Living cell with 2 neighbors survives") {
        grid.clear();
        grid.setCell(5, 5, true);  // Target cell
        grid.setCell(4, 5, true);  // Neighbor 1
        grid.setCell(5, 4, true);  // Neighbor 2
        
        REQUIRE(grid.getCell(5, 5) == true);
        REQUIRE(grid.countNeighbors(5, 5, false) == 2);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == true);
    }
    
    SECTION("Living cell with 3 neighbors survives") {
        grid.clear();
        grid.setCell(5, 5, true);  // Target cell
        grid.setCell(4, 5, true);  // Neighbor 1
        grid.setCell(5, 4, true);  // Neighbor 2
        grid.setCell(6, 5, true);  // Neighbor 3
        
        REQUIRE(grid.getCell(5, 5) == true);
        REQUIRE(grid.countNeighbors(5, 5, false) == 3);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == true);
    }
}

TEST_CASE("Conway's Rule 3: Death", "[rules][death]") {
    GameEngine engine(10, 10);
    Grid& grid = engine.getCurrentGridMutable();
    
    SECTION("Living cell with 0 neighbors dies (underpopulation)") {
        grid.clear();
        grid.setCell(5, 5, true);
        
        REQUIRE(grid.getCell(5, 5) == true);
        REQUIRE(grid.countNeighbors(5, 5, false) == 0);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == false);
    }
    
    SECTION("Living cell with 1 neighbor dies (underpopulation)") {
        grid.clear();
        grid.setCell(5, 5, true);
        grid.setCell(4, 5, true);
        
        REQUIRE(grid.getCell(5, 5) == true);
        REQUIRE(grid.countNeighbors(5, 5, false) == 1);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == false);
    }
    
    SECTION("Living cell with 4 neighbors dies (overpopulation)") {
        grid.clear();
        grid.setCell(5, 5, true);
        grid.setCell(4, 4, true);
        grid.setCell(4, 5, true);
        grid.setCell(5, 4, true);
        grid.setCell(6, 5, true);
        
        REQUIRE(grid.getCell(5, 5) == true);
        REQUIRE(grid.countNeighbors(5, 5, false) == 4);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == false);
    }
    
    SECTION("Living cell with 8 neighbors dies (overpopulation)") {
        grid.clear();
        grid.setCell(5, 5, true);
        // Surround with 8 neighbors
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr != 0 || dc != 0) {
                    grid.setCell(5 + dr, 5 + dc, true);
                }
            }
        }
        
        REQUIRE(grid.getCell(5, 5) == true);
        REQUIRE(grid.countNeighbors(5, 5, false) == 8);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().getCell(5, 5) == false);
    }
}

TEST_CASE("Classic patterns", "[patterns]") {
    SECTION("Block (still life)") {
        GameEngine engine(10, 10);
        Grid& grid = engine.getCurrentGridMutable();
        grid.clear();
        
        // Create 2x2 block
        grid.setCell(4, 4, true);
        grid.setCell(4, 5, true);
        grid.setCell(5, 4, true);
        grid.setCell(5, 5, true);
        
        Grid initial = grid;
        engine.step();
        
        // Block should remain unchanged
        REQUIRE(engine.getCurrentGrid() == initial);
    }
    
    SECTION("Blinker (period 2 oscillator)") {
        GameEngine engine(10, 10);
        Grid& grid = engine.getCurrentGridMutable();
        grid.clear();
        
        // Horizontal blinker
        grid.setCell(5, 4, true);
        grid.setCell(5, 5, true);
        grid.setCell(5, 6, true);
        
        Grid horizontal = grid;
        engine.step();
        
        // Should become vertical
        const Grid& vertical = engine.getCurrentGrid();
        REQUIRE(vertical.getCell(4, 5) == true);
        REQUIRE(vertical.getCell(5, 5) == true);
        REQUIRE(vertical.getCell(6, 5) == true);
        REQUIRE(vertical.getCell(5, 4) == false);
        REQUIRE(vertical.getCell(5, 6) == false);
        
        engine.step();
        
        // Should return to horizontal
        REQUIRE(engine.getCurrentGrid() == horizontal);
    }
}

TEST_CASE("GameEngine generation counter", "[engine]") {
    GameEngine engine(10, 10);
    
    SECTION("Initial generation is 0") {
        REQUIRE(engine.getGeneration() == 0);
    }
    
    SECTION("Generation increments with each step") {
        engine.step();
        REQUIRE(engine.getGeneration() == 1);
        
        engine.step();
        REQUIRE(engine.getGeneration() == 2);
        
        engine.step();
        REQUIRE(engine.getGeneration() == 3);
    }
    
    SECTION("Reset generation") {
        engine.step();
        engine.step();
        engine.step();
        REQUIRE(engine.getGeneration() == 3);
        
        engine.resetGeneration();
        REQUIRE(engine.getGeneration() == 0);
    }
}

TEST_CASE("Edge cases", "[edge-cases]") {
    SECTION("Empty grid stays empty") {
        GameEngine engine(10, 10);
        engine.getCurrentGridMutable().clear();
        
        REQUIRE(engine.getCurrentGrid().countLiving() == 0);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().countLiving() == 0);
    }
    
    SECTION("Single cell dies") {
        GameEngine engine(10, 10);
        Grid& grid = engine.getCurrentGridMutable();
        grid.clear();
        grid.setCell(5, 5, true);
        
        REQUIRE(grid.countLiving() == 1);
        
        engine.step();
        
        REQUIRE(engine.getCurrentGrid().countLiving() == 0);
    }
}
