#include <SFML/Graphics.hpp>
#include "../Graphics/mapRenderer.hpp"

int main()
{
	const auto mapW = 100;
	const auto mapH = 100;
	sf::RenderWindow window( sf::VideoMode( { mapW * 4 + 100, mapH * 4 + 8 } ), "Map Generator", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	std::vector<std::tuple<int, int, char>> userDefinedCellsTest = { {5, 5, 'O'}, {20, 15, 'O'}, {6,6,'O'} };


	MapRenderer newMap(mapW, mapH, userDefinedCellsTest);
	std::vector<std::vector<Cell*>> newMapCells = newMap.getCellMap();

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		for(int i = 0; i < 20; i++){
			newMap.generateMap(window);
		}
		
		window.clear(sf::Color(173, 156, 154));
		newMap.initialMapDraw(window);
		window.display();
	}

}