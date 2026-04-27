#include "./button.hpp"

Button::Button(int xPos, int yPos, int buttonWidth, int buttonHeight,
               std::string inButtonText, sf::Font& font)
    : buttonText(font, inButtonText, 18)
{
    buttonBorder.setPosition({
        static_cast<float>(xPos),
        static_cast<float>(yPos)
    });

    buttonBorder.setSize({
        static_cast<float>(buttonWidth),
        static_cast<float>(buttonHeight)
    });

    buttonBorder.setFillColor(sf::Color(46, 56, 140));
    buttonBorder.setOutlineColor(sf::Color::Black);
    buttonBorder.setOutlineThickness(2.f);

    buttonText.setFillColor(sf::Color::Black);
    buttonText.setCharacterSize(18);

    const sf::FloatRect textBounds = buttonText.getLocalBounds();

    buttonText.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
    });

    buttonText.setPosition({
        static_cast<float>(xPos) + static_cast<float>(buttonWidth) / 2.f,
        static_cast<float>(yPos) + static_cast<float>(buttonHeight) / 2.f
    });
}


void Button::drawButton(sf::RenderWindow &window){
    window.draw(buttonBorder);
    window.draw(buttonText);
}