#include "Grid.hpp"
#include "GameEngine.hpp"
#include "TextFileIO.hpp"
#include "Config.hpp"
#include "EnhancedGUIRenderer.hpp"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    try {
        // Parse configuration
        Config config;
        config.parse(argc, argv);
        
        // Load or create grid
        std::unique_ptr<Grid> grid;
        
        if (!config.getFilePath().empty()) {
            // Load from file
            TextFileIO fileIO;
            grid = fileIO.loadGrid(config.getFilePath());
            std::cout << "Loaded grid from: " << config.getFilePath() << "\n";
        } else {
            // Create default grid
            grid = std::make_unique<Grid>(80, 80);
            
            // Add a glider in the center
            int centerRow = grid->getRows() / 2;
            int centerCol = grid->getCols() / 2;
            grid->setCell(centerRow, centerCol + 1, true);
            grid->setCell(centerRow + 1, centerCol + 2, true);
            grid->setCell(centerRow + 2, centerCol, true);
            grid->setCell(centerRow + 2, centerCol + 1, true);
            grid->setCell(centerRow + 2, centerCol + 2, true);
            
            std::cout << "Created default 80x80 grid with glider\n";
        }
        
        std::cout << "Grid size: " << grid->getRows() << "x" << grid->getCols() << "\n";
        std::cout << "Starting GUI...\n\n";
        
        // Create game engine
        GameEngine engine(*grid, config.isToroidal());
        
        // Create and run enhanced GUI renderer
        EnhancedGUIRenderer renderer(engine, config);
        
        std::cout << "=== WELCOME TO CONWAY'S GAME OF LIFE ===\n";
        std::cout << "Press H for controls\n";
        std::cout << "Press K to cycle through beautiful themes!\n";
        std::cout << "Have fun! ✨\n\n";
        
        renderer.run();
        
        std::cout << "\nThanks for playing!\n";
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << "\n" << Config::getUsage();
        return 1;
    }
}
