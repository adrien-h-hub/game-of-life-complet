#include "TimelineManager.hpp"
#include <algorithm>

TimelineManager::TimelineManager(int maxHistorySize)
    : currentIndex_(0), maxHistorySize_(maxHistorySize), playbackSpeed_(1.0f) {
}

void TimelineManager::record(const Grid& grid, int generation) {
    // Remove future frames if we're in the middle of timeline
    if (currentIndex_ < static_cast<int>(timeline_.size()) - 1) {
        timeline_.erase(timeline_.begin() + currentIndex_ + 1, timeline_.end());
        
        // Remove bookmarks beyond current point
        auto it = bookmarks_.begin();
        while (it != bookmarks_.end()) {
            if (it->first > currentIndex_) {
                it = bookmarks_.erase(it);
            } else {
                ++it;
            }
        }
    }
    
    timeline_.push_back({grid, generation});
    
    // Limit timeline size
    if (static_cast<int>(timeline_.size()) > maxHistorySize_) {
        timeline_.pop_front();
        
        // Adjust bookmarks
        std::map<int, std::string> newBookmarks;
        for (const auto& bookmark : bookmarks_) {
            if (bookmark.first > 0) {
                newBookmarks[bookmark.first - 1] = bookmark.second;
            }
        }
        bookmarks_ = newBookmarks;
    } else {
        currentIndex_++;
    }
}

void TimelineManager::clear() {
    timeline_.clear();
    bookmarks_.clear();
    currentIndex_ = 0;
}

Grid TimelineManager::getFrame(int index) const {
    if (index >= 0 && index < static_cast<int>(timeline_.size())) {
        return timeline_[index].grid;
    }
    if (!timeline_.empty()) {
        return timeline_[currentIndex_].grid;
    }
    return Grid(50, 50); // Default empty grid
}

int TimelineManager::getGeneration(int index) const {
    if (index >= 0 && index < static_cast<int>(timeline_.size())) {
        return timeline_[index].generation;
    }
    return 0;
}

void TimelineManager::setCurrentIndex(int index) {
    if (index >= 0 && index < static_cast<int>(timeline_.size())) {
        currentIndex_ = index;
    }
}

void TimelineManager::next() {
    if (currentIndex_ < static_cast<int>(timeline_.size()) - 1) {
        currentIndex_++;
    }
}

void TimelineManager::previous() {
    if (currentIndex_ > 0) {
        currentIndex_--;
    }
}

void TimelineManager::jumpToStart() {
    currentIndex_ = 0;
}

void TimelineManager::jumpToEnd() {
    if (!timeline_.empty()) {
        currentIndex_ = static_cast<int>(timeline_.size()) - 1;
    }
}

void TimelineManager::jumpToGeneration(int generation) {
    for (int i = 0; i < static_cast<int>(timeline_.size()); ++i) {
        if (timeline_[i].generation == generation) {
            currentIndex_ = i;
            return;
        }
    }
}

void TimelineManager::addBookmark(int index, const std::string& label) {
    if (index >= 0 && index < static_cast<int>(timeline_.size())) {
        bookmarks_[index] = label.empty() ? "Bookmark" : label;
    }
}

void TimelineManager::removeBookmark(int index) {
    bookmarks_.erase(index);
}

std::vector<int> TimelineManager::getBookmarks() const {
    std::vector<int> result;
    for (const auto& bookmark : bookmarks_) {
        result.push_back(bookmark.first);
    }
    return result;
}

std::string TimelineManager::getBookmarkLabel(int index) const {
    auto it = bookmarks_.find(index);
    if (it != bookmarks_.end()) {
        return it->second;
    }
    return "";
}
