#include <SFML/Graphics.hpp>

class Button{
    private:
        sf::RectangleShape buttonRect;
        sf::Text buttonText;

    public:
        
        Button(int width, int height, std::string inputText, float xPos, float yPos, sf::Color inputColor);
        void drawButton(sf::RenderWindow &window);
        sf::RectangleShape &getButton(){ return buttonRect; }
        sf::Text &getText(){ return buttonText; }
};