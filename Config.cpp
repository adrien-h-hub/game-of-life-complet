#include "Config.hpp"
#include <iostream>
#include <sstream>

Config::Config()
    : filePath_(""),
      stepMs_(200),
      cellSize_(10),
      toroidal_(false),
      showGrid_(true) {
}

bool Config::parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        try {
            parseArgument(argv[i]);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing argument: " << argv[i] << "\n";
            std::cerr << e.what() << "\n";
            return false;
        }
    }
    return isValid();
}

void Config::parseArgument(const std::string& arg) {
    auto [key, value] = splitArgument(arg);
    
    if (key == "--file") {
        filePath_ = value;
    }
    else if (key == "--step-ms") {
        stepMs_ = std::stoi(value);
        if (stepMs_ < 10) {
            throw std::invalid_argument("step-ms must be at least 10");
        }
    }
    else if (key == "--cell-size") {
        cellSize_ = std::stoi(value);
        if (cellSize_ < 1 || cellSize_ > 100) {
            throw std::invalid_argument("cell-size must be between 1 and 100");
        }
    }
    else if (key == "--toroidal") {
        toroidal_ = (value == "1" || value == "true");
    }
    else if (key == "--grid") {
        showGrid_ = (value == "1" || value == "true");
    }
    else {
        throw std::invalid_argument("Unknown argument: " + key);
    }
}

std::pair<std::string, std::string> Config::splitArgument(const std::string& arg) {
    size_t equalPos = arg.find('=');
    if (equalPos == std::string::npos) {
        throw std::invalid_argument("Invalid argument format (expected key=value): " + arg);
    }
    
    std::string key = arg.substr(0, equalPos);
    std::string value = arg.substr(equalPos + 1);
    
    return {key, value};
}

bool Config::isValid() const {
    return true; // File is optional, we'll create a default grid
}

std::string Config::getUsage() {
    std::ostringstream oss;
    oss << "Usage: GameOfLife.exe [OPTIONS]\n\n";
    oss << "Options:\n";
    oss << "  --file=PATH             Input file path (optional)\n";
    oss << "  --step-ms=INT           Milliseconds between generations (default: 200)\n";
    oss << "  --cell-size=INT         Cell size in pixels (default: 10)\n";
    oss << "  --toroidal=0|1          Enable toroidal mode (default: 0)\n";
    oss << "  --grid=0|1              Show grid lines (default: 1)\n\n";
    oss << "Example:\n";
    oss << "  GameOfLife.exe --file=patterns/glider.txt --cell-size=15\n";
    return oss.str();
}
