#include "UIButton.hpp"
#include <cmath>

UIButton::UIButton(const std::string& text, float x, float y, float width, float height, Style style)
    : x_(x), y_(y), width_(width), height_(height), style_(style),
      enabled_(true), isHovered_(false), isPressed_(false), toggled_(false), icon_(text) {
    
    shape_.setPosition(sf::Vector2f(x, y));
    shape_.setSize(sf::Vector2f(width, height));
    
    // Rounded corners effect
    shape_.setOutlineThickness(2.0f);
}

void UIButton::setPosition(float x, float y) {
    x_ = x;
    y_ = y;
    shape_.setPosition(sf::Vector2f(x, y));
}

void UIButton::setSize(float width, float height) {
    width_ = width;
    height_ = height;
    shape_.setSize(sf::Vector2f(width, height));
}

void UIButton::setText(const std::string& text) {
    icon_ = text;  // Store as icon string, will be created with font during render
}

void UIButton::setIcon(const std::string& icon) {
    icon_ = icon;
}

void UIButton::setCallback(std::function<void()> callback) {
    callback_ = callback;
}

void UIButton::setEnabled(bool enabled) {
    enabled_ = enabled;
}

void UIButton::setToggled(bool toggled) {
    toggled_ = toggled;
}

bool UIButton::contains(float x, float y) const {
    return x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_;
}

void UIButton::handleHover(bool isHovered) {
    isHovered_ = isHovered && enabled_;
}

void UIButton::handleClick() {
    if (enabled_ && callback_) {
        callback_();
    }
}

UIButton::Colors UIButton::getColorsForStyle() const {
    Colors colors;
    
    switch (style_) {
        case Style::PRIMARY:
            colors.normal = sf::Color(70, 130, 220);      // Beautiful blue
            colors.hover = sf::Color(90, 150, 240);
            colors.pressed = sf::Color(50, 110, 200);
            colors.disabled = sf::Color(100, 100, 100);
            colors.text = sf::Color::White;
            break;
            
        case Style::SUCCESS:
            colors.normal = sf::Color(46, 204, 113);      // Green
            colors.hover = sf::Color(66, 224, 133);
            colors.pressed = sf::Color(26, 184, 93);
            colors.disabled = sf::Color(100, 100, 100);
            colors.text = sf::Color::White;
            break;
            
        case Style::DANGER:
            colors.normal = sf::Color(231, 76, 60);       // Red
            colors.hover = sf::Color(241, 96, 80);
            colors.pressed = sf::Color(211, 56, 40);
            colors.disabled = sf::Color(100, 100, 100);
            colors.text = sf::Color::White;
            break;
            
        case Style::INFO:
            colors.normal = sf::Color(52, 152, 219);      // Light blue
            colors.hover = sf::Color(72, 172, 239);
            colors.pressed = sf::Color(32, 132, 199);
            colors.disabled = sf::Color(100, 100, 100);
            colors.text = sf::Color::White;
            break;
            
        case Style::SECONDARY:
            colors.normal = sf::Color(149, 165, 166);     // Gray
            colors.hover = sf::Color(169, 185, 186);
            colors.pressed = sf::Color(129, 145, 146);
            colors.disabled = sf::Color(100, 100, 100);
            colors.text = sf::Color::White;
            break;
            
        case Style::ICON:
            colors.normal = sf::Color(0, 0, 0, 0);        // Transparent
            colors.hover = sf::Color(255, 255, 255, 20);  // Slight highlight
            colors.pressed = sf::Color(255, 255, 255, 40);
            colors.disabled = sf::Color(0, 0, 0, 0);
            colors.text = sf::Color(200, 200, 200);
            break;
    }
    
    return colors;
}

void UIButton::updateVisuals(const sf::Font& font) {
    Colors colors = getColorsForStyle();
    
    // Determine current color based on state
    sf::Color currentColor;
    if (!enabled_) {
        currentColor = colors.disabled;
    } else if (isPressed_) {
        currentColor = colors.pressed;
    } else if (isHovered_) {
        currentColor = colors.hover;
    } else if (toggled_) {
        currentColor = colors.pressed; // Toggled buttons stay highlighted
    } else {
        currentColor = colors.normal;
    }
    
    shape_.setFillColor(currentColor);
    
    // Outline color
    if (toggled_) {
        shape_.setOutlineColor(sf::Color(255, 215, 0)); // Gold outline when toggled
    } else if (isHovered_ && enabled_) {
        shape_.setOutlineColor(sf::Color(255, 255, 255, 100));
    } else {
        shape_.setOutlineColor(sf::Color(255, 255, 255, 50));
    }
    
    // Text will be created and positioned during render with proper font
}

void UIButton::render(sf::RenderWindow& window, const sf::Font& font) {
    updateVisuals(font);
    
    // Add subtle shadow effect
    if (enabled_ && !isPressed_) {
        sf::RectangleShape shadow = shape_;
        shadow.setPosition(sf::Vector2f(x_ + 2, y_ + 2));
        shadow.setFillColor(sf::Color(0, 0, 0, 30));
        shadow.setOutlineThickness(0);
        window.draw(shadow);
    }
    
    window.draw(shape_);
    
    // Draw text (SFML 3.0 compatible)
    if (!icon_.empty()) {
        Colors colors = getColorsForStyle();
        sf::Color textColor = enabled_ ? colors.text : sf::Color(150, 150, 150);
        
        sf::Text buttonText(font, icon_, 14);
        buttonText.setFillColor(textColor);
        
        sf::FloatRect textBounds = buttonText.getLocalBounds();
        
        // Center text in button (SFML 3.0: use .position and .size directly)
        buttonText.setPosition(sf::Vector2f(
            x_ + (width_ - textBounds.size.x) / 2.0f - textBounds.position.x,
            y_ + (height_ - textBounds.size.y) / 2.0f - textBounds.position.y - 2.0f
        ));
        
        window.draw(buttonText);
    }
}

// ============================================================================
// UIPanel Implementation
// ============================================================================

UIPanel::UIPanel(float x, float y, float width, float height, const std::string& title)
    : x_(x), y_(y), width_(width), height_(height), title_(title), visible_(true) {
    
    // Background with modern gradient-like look (darker at top)
    background_.setPosition(sf::Vector2f(x, y));
    background_.setSize(sf::Vector2f(width, height));
    background_.setFillColor(sf::Color(30, 30, 40, 240)); // Dark with transparency
    background_.setOutlineThickness(2.0f);
    background_.setOutlineColor(sf::Color(70, 70, 90, 200));
    
    // Title bar
    titleBar_.setPosition(sf::Vector2f(x, y));
    titleBar_.setSize(sf::Vector2f(width, 35));
    titleBar_.setFillColor(sf::Color(45, 45, 60, 250));
}

void UIPanel::setPosition(float x, float y) {
    x_ = x;
    y_ = y;
    background_.setPosition(sf::Vector2f(x, y));
    titleBar_.setPosition(sf::Vector2f(x, y));
}

void UIPanel::setTitle(const std::string& title) {
    title_ = title;
}

void UIPanel::render(sf::RenderWindow& window, const sf::Font& font) {
    if (!visible_) return;
    
    // Draw subtle drop shadow
    sf::RectangleShape shadow = background_;
    shadow.setPosition(sf::Vector2f(x_ + 4, y_ + 4));
    shadow.setFillColor(sf::Color(0, 0, 0, 60));
    shadow.setOutlineThickness(0);
    window.draw(shadow);
    
    // Draw main background
    window.draw(background_);
    
    // Draw title bar if title exists
    if (!title_.empty()) {
        window.draw(titleBar_);
        
        // Title text (SFML 3.0 compatible)
        sf::Text titleText(font, title_, 16);
        titleText.setFillColor(sf::Color(220, 220, 240));
        titleText.setStyle(sf::Text::Bold);
        titleText.setPosition(sf::Vector2f(x_ + 15, y_ + 8));
        window.draw(titleText);
    }
}
