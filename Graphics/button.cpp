#include "../Graphics/button.hpp"

Button::Button(int width, int height, std::string inputText, float xPos, float yPos, sf::Color inputColor){
    this->buttonRect.setSize(sf::Vector2f(width, height));
    this->buttonRect.setFillColor(inputColor);
    this->buttonRect.setPosition(sf::Vector2f(xPos, yPos));
    this->buttonRect.setOutlineColor(sf::Color::Black);
    this->buttonRect.setOutlineThickness(3);
    
    this->buttonText.setString(inputText);
    this->buttonText.setPosition(buttonRect.getPosition());
    this->buttonText.setFillColor(sf::Color::Black);
}

void Button::drawButton(sf::RenderWindow &window){
    window.draw(getButton());
    window.draw(getText());
}