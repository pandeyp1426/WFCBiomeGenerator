#include <SFML/Graphics.hpp>
#include "../Graphics/mapRenderer.hpp"

int main()
{
	const auto mapW = 200;
	const auto mapH = 200;
	sf::RenderWindow window( sf::VideoMode( { mapW * 4, mapH * 4 } ), "Map Generator", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	std::vector<std::tuple<int, int, char>> userDefinedCellsTest = { 
		{75,75,'I'},{75,76,'I'},{75,77,'I'},
	 	{74,75,'I'},{74,76,'I'},{74,77,'I'}};


	MapRenderer newMap(mapW, mapH, userDefinedCellsTest);
	std::vector<std::vector<Cell*>> newMapCells = newMap.getCellMap();

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