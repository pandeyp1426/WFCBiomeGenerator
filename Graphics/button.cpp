#include "./button.hpp"

Button::Button(int xPos, int yPos, int buttonWidth, int buttonHeight, std::string inButtonText){
    this->xPos = xPos;
    this->yPos = yPos;
    this->buttonWidth = buttonWidth;
    this->buttonHeight = buttonHeight;

    
    buttonBorder.setFillColor(sf::Color::Green);
    buttonBorder.setOutlineColor(sf::Color::Red);
    buttonBorder.setOutlineThickness(2);
    buttonBorder.setPosition(sf::Vector2f(xPos, yPos));
    
    if(!buttonFont.openFromFile(".\\Fonts\\OpenSans.ttf")) return;
    buttonText = sf::Text(buttonFont);
    buttonText.setString(inButtonText);
    buttonText.setCharacterSize(10);
    buttonText.setPosition(sf::Vector2f(xPos, yPos));
}

void Button::drawButton(sf::RenderWindow &window){
    window.draw(buttonBorder);
    window.draw(buttonText);
}