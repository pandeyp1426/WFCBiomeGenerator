//#include <SFML/Graphics.hpp>
#include "../BiomeClasses/map.hpp"

int main()
{
	// sf::RenderWindow window( sf::VideoMode( { 200, 200 } ), "SFML works!" );
	// sf::RectangleShape shape({50, 100});
	// shape.setFillColor( sf::Color::Green );

	// while ( window.isOpen() )
	// {
	// 	while ( const std::optional event = window.pollEvent() )
	// 	{
	// 		if ( event->is<sf::Event::Closed>() )
	// 			window.close();
	// 	}

	// 	window.clear();
	// 	window.draw( shape );
	// 	window.display();
	// }

	std::vector<std::tuple<int,int,char>> userDefinedCellsTest = {{5, 5, 'C'}, {20, 15, 'F'}};


	Map newMap(30, 20, userDefinedCellsTest);
	std::cout << "Map object made\n";
	newMap.printMap();
	std::cout << "\n\n\n";
	std::cout << "Map Generate:\n";
	newMap.generateMap();
	newMap.printMap();

}
