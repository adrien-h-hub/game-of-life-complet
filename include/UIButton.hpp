#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

/**
 * @class UIButton
 * @brief Beautiful, interactive button for modern GUI
 */
class UIButton {
public:
    enum class Style {
        PRIMARY,    // Main actions (Play, Pause)
        SECONDARY,  // Less important actions
        SUCCESS,    // Positive actions (Save)
        DANGER,     // Destructive actions (Clear)
        INFO,       // Informational
        ICON        // Icon-only button
    };
    
    UIButton(const std::string& text, float x, float y, float width, float height, 
             Style style = Style::PRIMARY);
    
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setText(const std::string& text);
    void setIcon(const std::string& icon);
    void setCallback(std::function<void()> callback);
    void setEnabled(bool enabled);
    void setToggled(bool toggled); // For toggle buttons
    
    bool contains(float x, float y) const;
    void handleHover(bool isHovered);
    void handleClick();
    
    void render(sf::RenderWindow& window, const sf::Font& font);
    
    bool isEnabled() const { return enabled_; }
    bool isToggled() const { return toggled_; }
    
private:
    sf::RectangleShape shape_;
    std::string icon_;  // Stores button text/icon
    std::function<void()> callback_;
    
    Style style_;
    bool enabled_;
    bool isHovered_;
    bool isPressed_;
    bool toggled_;
    
    float x_, y_, width_, height_;
    
    // Beautiful color schemes
    struct Colors {
        sf::Color normal;
        sf::Color hover;
        sf::Color pressed;
        sf::Color disabled;
        sf::Color text;
    };
    
    Colors getColorsForStyle() const;
    void updateVisuals(const sf::Font& font);
};

/**
 * @class UIPanel
 * @brief Modern panel/container for UI elements
 */
class UIPanel {
public:
    UIPanel(float x, float y, float width, float height, 
            const std::string& title = "");
    
    void setPosition(float x, float y);
    void setTitle(const std::string& title);
    void setVisible(bool visible) { visible_ = visible; }
    bool isVisible() const { return visible_; }
    
    void render(sf::RenderWindow& window, const sf::Font& font);
    
private:
    float x_, y_, width_, height_;
    std::string title_;
    bool visible_;
    
    sf::RectangleShape background_;
    sf::RectangleShape titleBar_;
};
