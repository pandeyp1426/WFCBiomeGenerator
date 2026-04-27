#include "button.hpp"

Button::Button(float xPos, float yPos, float buttonWidth, float buttonHeight, const std::string& inButtonText)
    : buttonText(buttonFont, inButtonText, 18)
{
    const char* fontPaths[] = {
        "Fonts/OpenSans.ttf",
        "Graphics/fonts/OpenSans.ttf",
        "../Graphics/fonts/OpenSans.ttf"
    };

    for (const char* fontPath : fontPaths)
    {
        if (buttonFont.openFromFile(fontPath))
            break;
    }

    buttonBorder.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    buttonBorder.setFillColor(sf::Color(48, 122, 89));
    buttonBorder.setOutlineColor(sf::Color(181, 231, 201));
    buttonBorder.setOutlineThickness(2);
    buttonBorder.setPosition(sf::Vector2f(xPos, yPos));

    buttonText.setFillColor(sf::Color::White);

    const auto textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(sf::Vector2f(
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f));
    buttonText.setPosition(sf::Vector2f(
        xPos + buttonWidth / 2.0f,
        yPos + buttonHeight / 2.0f));
}

void Button::drawButton(sf::RenderTarget& target) const
{
    target.draw(buttonBorder);
    target.draw(buttonText);
}

bool Button::contains(sf::Vector2f point) const
{
    return buttonBorder.getGlobalBounds().contains(point);
}
