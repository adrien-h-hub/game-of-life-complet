#include "TextFileIO.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::unique_ptr<Grid> TextFileIO::loadGrid(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    int rows, cols;
    file >> rows >> cols;
    
    if (file.fail() || rows <= 0 || cols <= 0) {
        throw std::runtime_error("Invalid grid dimensions in file: " + filename);
    }
    
    auto grid = std::make_unique<Grid>(rows, cols);
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int value;
            file >> value;
            
            if (file.fail()) {
                throw std::runtime_error("Unexpected end of file or invalid data");
            }
            
            if (value != 0 && value != 1) {
                throw std::runtime_error("Invalid cell value (must be 0 or 1)");
            }
            
            grid->setCell(row, col, value == 1);
        }
    }
    
    file.close();
    return grid;
}

void TextFileIO::saveGrid(const Grid& grid, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    file << grid.getRows() << " " << grid.getCols() << "\n";
    
    for (int row = 0; row < grid.getRows(); ++row) {
        for (int col = 0; col < grid.getCols(); ++col) {
            file << (grid.getCell(row, col) ? "1" : "0");
            if (col < grid.getCols() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
    
    file.close();
}
