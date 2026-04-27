#include <SFML/Graphics.hpp>
#include "../Graphics/mapRenderer.hpp"
#include "../Graphics/button.hpp"

int main()
{
	const auto mapW = 100;
	const auto mapH = 100;
	const int cellSize = 4;
	int windowWidth = mapW * 4 + 200;
	int windowHeight = mapH * 4 + 8;

	sf::Font uiFont;
	if(!uiFont.openFromFile("../../../../Graphics/fonts/OpenSans.ttf")){
		throw std::runtime_error("Failed to load font");
	}

	std::string randomizeString = "Randomize";

	Button randomSeedButton(windowWidth - 180, 10, 150, 40, randomizeString, uiFont);

	sf::RenderWindow window( sf::VideoMode( { static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight) } ), "Map Generator", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	std::vector<std::tuple<int, int, char>> userDefinedCellsTest = { {5, 5, 'O'} };
	std::vector<std::tuple<int,int,char>> userTest = {{50, 50, 'F'}};


	MapRenderer newMap(mapW, mapH, userDefinedCellsTest);
	std::vector<std::vector<Cell*>> newMapCells = newMap.getCellMap();

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();

			for(int i = 0; i < 20; i++){
				newMap.generateMap(window);
			}
			
			window.clear(sf::Color(173, 156, 154));
			newMap.initialMapDraw(window);
			randomSeedButton.drawButton(window);
			window.display();
		}
	}

}