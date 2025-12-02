#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <memory>

class Grid {
public:
    Grid(int rows, int cols);
    Grid(const Grid& other);
    Grid& operator=(const Grid& other);
    
    int getRows() const { return rows_; }
    int getCols() const { return cols_; }
    bool getCell(int row, int col) const;
    void setCell(int row, int col, bool alive);
    void toggleCell(int row, int col);
    int countNeighbors(int row, int col, bool toroidal = false) const;
    void clear();
    int countLiving() const;
    bool operator==(const Grid& other) const;
    std::string toString() const;
    
    // File I/O methods for console mode
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    void printGrid() const;  // Console display

private:
    int rows_;
    int cols_;
    std::vector<std::vector<bool>> cells_;
    bool isValidPosition(int row, int col) const;
};

#endif
