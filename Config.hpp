#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config {
public:
    Config();
    bool parse(int argc, char* argv[]);
    
    std::string getFilePath() const { return filePath_; }
    int getStepMs() const { return stepMs_; }
    int getCellSize() const { return cellSize_; }
    bool isToroidal() const { return toroidal_; }
    bool showGrid() const { return showGrid_; }
    bool isValid() const;
    static std::string getUsage();

private:
    std::string filePath_;
    int stepMs_;
    int cellSize_;
    bool toroidal_;
    bool showGrid_;
    
    void parseArgument(const std::string& arg);
    static std::pair<std::string, std::string> splitArgument(const std::string& arg);
};

#endif
