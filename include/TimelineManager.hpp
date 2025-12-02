#pragma once
#include "Grid.hpp"
#include <vector>
#include <deque>
#include <map>
#include <string>

/**
 * @class TimelineManager
 * @brief Manages simulation history and timeline navigation
 */
class TimelineManager {
public:
    TimelineManager(int maxHistorySize = 1000);
    
    // Recording
    void record(const Grid& grid, int generation);
    void clear();
    
    // Navigation
    Grid getFrame(int index) const;
    int getCurrentIndex() const { return currentIndex_; }
    int getFrameCount() const { return static_cast<int>(timeline_.size()); }
    int getGeneration(int index) const;
    
    void setCurrentIndex(int index);
    void next();
    void previous();
    void jumpToStart();
    void jumpToEnd();
    void jumpToGeneration(int generation);
    
    // Bookmarks
    void addBookmark(int index, const std::string& label = "");
    void removeBookmark(int index);
    std::vector<int> getBookmarks() const;
    std::string getBookmarkLabel(int index) const;
    
    // Playback
    void setPlaybackSpeed(float speed) { playbackSpeed_ = speed; }
    float getPlaybackSpeed() const { return playbackSpeed_; }
    
private:
    struct Frame {
        Grid grid;
        int generation;
    };
    
    std::deque<Frame> timeline_;
    int currentIndex_;
    int maxHistorySize_;
    std::map<int, std::string> bookmarks_;
    float playbackSpeed_;
};
