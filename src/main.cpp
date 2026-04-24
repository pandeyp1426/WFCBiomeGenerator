#include <SFML/Graphics.hpp>
#include "../Graphics/mapRenderer.hpp"
#include "../Graphics/button.hpp"

int main()
{
	const auto mapW = 200;
	const auto mapH = 200;
	sf::RenderWindow window( sf::VideoMode( { mapW * 4, mapH * 4 } ), "Map Generator", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	std::vector<std::tuple<int, int, char>> userDefinedCellsTest = {
		{100,100,'P'} };


	MapRenderer newMap(mapW, mapH, userDefinedCellsTest);
	std::vector<std::vector<Cell*>> newMapCells = newMap.getCellMap();

	Button generateButton(40, 20, "Generate Map", static_cast<float>(mapW - 20), static_cast<float>(mapH - 20), sf::Color::Green)

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		for(int i = 0; i < 30; i++){
			newMap.generateMap(window);
		}
		
		window.clear();
		newMap.initialMapDraw(window);
		window.display();
	}

}