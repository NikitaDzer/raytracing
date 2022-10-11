#include <SFML/Graphics.hpp>

#include "../include/window.h"


void init_window( sf::RenderWindow &window)
{
	sf::VideoMode video_mode = { WINDOW_WIDTH, WINDOW_HEIGHT };
	
	window.create( video_mode, WINDOW_NAME);
	window.setFramerateLimit( FRAMERATE_LIMIT);

	window.clear( COLOR_BG);
	window.display();
}	
