#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics.hpp>

class Button{
    private:
        sf::RectangleShape buttonBorder;
        sf::Font buttonFont;
        sf::Text buttonText;
        int xPos, yPos, buttonWidth, buttonHeight;

    public:
        Button(int xPos, int yPos, int buttonWidth, int buttonHeight, std::string inButtonText);
        void drawButton(sf::RenderWindow &window);
};