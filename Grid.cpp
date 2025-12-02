#include "Grid.hpp"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>

Grid::Grid(int rows, int cols) 
    : rows_(rows), cols_(cols), cells_(rows, std::vector<bool>(cols, false)) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Grid dimensions must be positive");
    }
}

Grid::Grid(const Grid& other) 
    : rows_(other.rows_), cols_(other.cols_), cells_(other.cells_) {
}

Grid& Grid::operator=(const Grid& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        cells_ = other.cells_;
    }
    return *this;
}

bool Grid::getCell(int row, int col) const {
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Cell position out of bounds");
    }
    return cells_[row][col];
}

void Grid::setCell(int row, int col, bool alive) {
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Cell position out of bounds");
    }
    cells_[row][col] = alive;
}

void Grid::toggleCell(int row, int col) {
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Cell position out of bounds");
    }
    cells_[row][col] = !cells_[row][col];
}

int Grid::countNeighbors(int row, int col, bool toroidal) const {
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Cell position out of bounds");
    }
    
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            
            int neighborRow = row + dr;
            int neighborCol = col + dc;
            
            if (toroidal) {
                neighborRow = (neighborRow + rows_) % rows_;
                neighborCol = (neighborCol + cols_) % cols_;
                if (cells_[neighborRow][neighborCol]) {
                    ++count;
                }
            } else {
                if (isValidPosition(neighborRow, neighborCol) && 
                    cells_[neighborRow][neighborCol]) {
                    ++count;
                }
            }
        }
    }
    return count;
}

void Grid::clear() {
    for (auto& row : cells_) {
        std::fill(row.begin(), row.end(), false);
    }
}

int Grid::countLiving() const {
    int count = 0;
    for (const auto& row : cells_) {
        count += std::count(row.begin(), row.end(), true);
    }
    return count;
}

bool Grid::operator==(const Grid& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    return cells_ == other.cells_;
}

std::string Grid::toString() const {
    std::ostringstream oss;
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            oss << (cells_[row][col] ? "█" : ".");
        }
        if (row < rows_ - 1) {
            oss << "\n";
        }
    }
    return oss.str();
}

bool Grid::isValidPosition(int row, int col) const {
    return row >= 0 && row < rows_ && col >= 0 && col < cols_;
}

// File I/O Implementation for Console Mode
bool Grid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for reading" << std::endl;
        return false;
    }
    
    int newRows, newCols;
    if (!(file >> newRows >> newCols)) {
        std::cerr << "Error: Invalid file format. Expected dimensions on first line." << std::endl;
        return false;
    }
    
    if (newRows <= 0 || newCols <= 0) {
        std::cerr << "Error: Invalid dimensions in file: " << newRows << "x" << newCols << std::endl;
        return false;
    }
    
    // Resize grid to new dimensions
    rows_ = newRows;
    cols_ = newCols;
    cells_.resize(rows_);
    for (auto& row : cells_) {
        row.resize(cols_, false);
    }
    
    // Read cell states
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            int value;
            if (!(file >> value)) {
                std::cerr << "Error: Not enough cell values in file" << std::endl;
                return false;
            }
            cells_[row][col] = (value == 1);
        }
    }
    
    file.close();
    return true;
}

bool Grid::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing" << std::endl;
        return false;
    }
    
    // Write dimensions on first line
    file << rows_ << " " << cols_ << "\n";
    
    // Write cell states
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            file << (cells_[row][col] ? "1" : "0");
            if (col < cols_ - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
    
    file.close();
    return true;
}

void Grid::printGrid() const {
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            std::cout << (cells_[row][col] ? "█" : ".");
        }
        std::cout << "\n";
    }
}
