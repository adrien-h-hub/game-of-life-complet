#ifndef TEXT_FILE_IO_HPP
#define TEXT_FILE_IO_HPP

#include "Grid.hpp"
#include <string>
#include <memory>

class TextFileIO {
public:
    std::unique_ptr<Grid> loadGrid(const std::string& filename);
    void saveGrid(const Grid& grid, const std::string& filename);
};

#endif
