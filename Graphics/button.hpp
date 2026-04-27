#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    sf::RectangleShape buttonBorder;
    sf::Font buttonFont;
    sf::Text buttonText;

public:
    Button(float xPos, float yPos, float buttonWidth, float buttonHeight, const std::string& inButtonText);

    void drawButton(sf::RenderTarget& target) const;
    bool contains(sf::Vector2f point) const;
};
