#include <SFML/Graphics.hpp>
#include "../Graphics/mapRenderer.hpp"

int main()
{
	const auto mapW = 500;
	const auto mapH = 300;
	sf::RenderWindow window( sf::VideoMode( { mapW * 4, mapH * 4 } ), "Map Generator", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	std::vector<std::tuple<int, int, char>> userDefinedCellsTest = { {250, 150, 'O'}, {251, 150, 'O'}, {252,150,'O'} };


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