#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string.h>

#include "include/window.h"
#include "include/vector.h"
#include "include/common.h"
#include "include/scene.h"


int main()
{
	sf::RenderWindow window = {};
	init_window( window);

	Camera camera = Vector( 0, 0, -500);
	Scene  scene  = {};

	while ( window.isOpen() )
    	{	
		if ( sf::Keyboard::isKeyPressed( KEY_EXIT) )
		{
			window.close();
			break;
		}

		scene.render( camera, window);
		scene.draw  ( window);
		window.display();

		// camera.coords( camera.coords() +  Vector( 0, 0, 0));
	}
	
	return 0;
}

