/**
 * @file test_grid.cpp
 * @brief Unit tests for Grid class using Catch2 v3
 */

#include <catch2/catch_test_macros.hpp>
#include "../Grid.hpp"

TEST_CASE("Grid construction", "[grid]") {
    SECTION("Valid dimensions") {
        Grid grid(10, 20);
        REQUIRE(grid.getRows() == 10);
        REQUIRE(grid.getCols() == 20);
        REQUIRE(grid.countLiving() == 0);
    }
    
    SECTION("Invalid dimensions throw exception") {
        REQUIRE_THROWS_AS(Grid(-1, 10), std::invalid_argument);
        REQUIRE_THROWS_AS(Grid(10, -1), std::invalid_argument);
        REQUIRE_THROWS_AS(Grid(0, 10), std::invalid_argument);
        REQUIRE_THROWS_AS(Grid(10, 0), std::invalid_argument);
    }
}

TEST_CASE("Grid cell operations", "[grid]") {
    Grid grid(10, 10);
    
    SECTION("Get and set cells") {
        REQUIRE(grid.getCell(5, 5) == false);
        
        grid.setCell(5, 5, true);
        REQUIRE(grid.getCell(5, 5) == true);
        
        grid.setCell(5, 5, false);
        REQUIRE(grid.getCell(5, 5) == false);
    }
    
    SECTION("Toggle cells") {
        REQUIRE(grid.getCell(3, 3) == false);
        
        grid.toggleCell(3, 3);
        REQUIRE(grid.getCell(3, 3) == true);
        
        grid.toggleCell(3, 3);
        REQUIRE(grid.getCell(3, 3) == false);
    }
    
    SECTION("Out of bounds access throws exception") {
        REQUIRE_THROWS_AS(grid.getCell(-1, 5), std::out_of_range);
        REQUIRE_THROWS_AS(grid.getCell(5, -1), std::out_of_range);
        REQUIRE_THROWS_AS(grid.getCell(10, 5), std::out_of_range);
        REQUIRE_THROWS_AS(grid.getCell(5, 10), std::out_of_range);
        
        REQUIRE_THROWS_AS(grid.setCell(-1, 5, true), std::out_of_range);
        REQUIRE_THROWS_AS(grid.setCell(15, 5, true), std::out_of_range);
    }
}

TEST_CASE("Grid neighbor counting - standard topology", "[grid][neighbors]") {
    Grid grid(10, 10);
    
    SECTION("Center cell with no neighbors") {
        REQUIRE(grid.countNeighbors(5, 5, false) == 0);
    }
    
    SECTION("Center cell with one neighbor") {
        grid.setCell(5, 5, true);
        REQUIRE(grid.countNeighbors(4, 4, false) == 1);
        REQUIRE(grid.countNeighbors(4, 5, false) == 1);
        REQUIRE(grid.countNeighbors(4, 6, false) == 1);
        REQUIRE(grid.countNeighbors(5, 4, false) == 1);
        REQUIRE(grid.countNeighbors(5, 6, false) == 1);
        REQUIRE(grid.countNeighbors(6, 4, false) == 1);
        REQUIRE(grid.countNeighbors(6, 5, false) == 1);
        REQUIRE(grid.countNeighbors(6, 6, false) == 1);
    }
    
    SECTION("Center cell surrounded by 8 neighbors") {
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr != 0 || dc != 0) {
                    grid.setCell(5 + dr, 5 + dc, true);
                }
            }
        }
        REQUIRE(grid.countNeighbors(5, 5, false) == 8);
    }
    
    SECTION("Corner cell (0,0) with neighbors") {
        grid.setCell(0, 1, true);
        grid.setCell(1, 0, true);
        grid.setCell(1, 1, true);
        REQUIRE(grid.countNeighbors(0, 0, false) == 3);
    }
    
    SECTION("Edge cell with partial neighbors") {
        grid.setCell(0, 4, true);
        grid.setCell(0, 5, true);
        grid.setCell(0, 6, true);
        REQUIRE(grid.countNeighbors(0, 5, false) == 2);  // Only right and left neighbors
    }
}

TEST_CASE("Grid neighbor counting - toroidal topology", "[grid][neighbors][toroidal]") {
    Grid grid(10, 10);
    
    SECTION("Corner cell (0,0) wraps around") {
        grid.setCell(0, 9, true);  // Left wraps
        grid.setCell(9, 0, true);  // Top wraps
        grid.setCell(9, 9, true);  // Diagonal wraps
        REQUIRE(grid.countNeighbors(0, 0, true) == 3);
    }
    
    SECTION("Top edge cell wraps to bottom") {
        grid.setCell(9, 5, true);  // Below wraps to top
        REQUIRE(grid.countNeighbors(0, 5, true) == 1);
    }
}

TEST_CASE("Grid clear and count", "[grid]") {
    Grid grid(5, 5);
    
    SECTION("Clear empty grid") {
        grid.clear();
        REQUIRE(grid.countLiving() == 0);
    }
    
    SECTION("Count living cells") {
        grid.setCell(0, 0, true);
        grid.setCell(2, 2, true);
        grid.setCell(4, 4, true);
        REQUIRE(grid.countLiving() == 3);
    }
    
    SECTION("Clear populated grid") {
        grid.setCell(1, 1, true);
        grid.setCell(2, 2, true);
        grid.setCell(3, 3, true);
        REQUIRE(grid.countLiving() == 3);
        
        grid.clear();
        REQUIRE(grid.countLiving() == 0);
    }
}

TEST_CASE("Grid copy and equality", "[grid]") {
    Grid grid1(5, 5);
    grid1.setCell(2, 2, true);
    grid1.setCell(2, 3, true);
    
    SECTION("Copy constructor") {
        Grid grid2(grid1);
        REQUIRE(grid2 == grid1);
        REQUIRE(grid2.getCell(2, 2) == true);
        REQUIRE(grid2.getCell(2, 3) == true);
    }
    
    SECTION("Assignment operator") {
        Grid grid2(10, 10);
        grid2 = grid1;
        REQUIRE(grid2 == grid1);
        REQUIRE(grid2.getRows() == grid1.getRows());
        REQUIRE(grid2.getCols() == grid1.getCols());
    }
    
    SECTION("Modified copy is not equal") {
        Grid grid2(grid1);
        grid2.setCell(2, 2, false);
        REQUIRE(grid2 != grid1);
    }
}

TEST_CASE("Grid file I/O", "[grid][io]") {
    const std::string testFile = "test_grid.txt";
    
    SECTION("Save and load grid") {
        Grid grid1(5, 5);
        grid1.setCell(1, 1, true);
        grid1.setCell(2, 2, true);
        grid1.setCell(3, 3, true);
        
        REQUIRE(grid1.saveToFile(testFile));
        
        Grid grid2(3, 3);  // Different size initially
        REQUIRE(grid2.loadFromFile(testFile));
        
        REQUIRE(grid2.getRows() == 5);
        REQUIRE(grid2.getCols() == 5);
        REQUIRE(grid2 == grid1);
    }
    
    SECTION("Load invalid file fails gracefully") {
        Grid grid(5, 5);
        REQUIRE_FALSE(grid.loadFromFile("nonexistent_file.txt"));
    }
}

TEST_CASE("Grid toString", "[grid]") {
    Grid grid(3, 3);
    
    SECTION("Empty grid") {
        std::string str = grid.toString();
        REQUIRE(str.find(".") != std::string::npos);
        REQUIRE(str.find("█") == std::string::npos);
    }
    
    SECTION("Grid with cells") {
        grid.setCell(0, 0, true);
        grid.setCell(1, 1, true);
        grid.setCell(2, 2, true);
        
        std::string str = grid.toString();
        REQUIRE(str.find("█") != std::string::npos);
    }
}
