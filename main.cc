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

	Camera camera = Vector( 0, 0, -100);
	Scene  scene  = {};

	while ( window.isOpen() )
    	{	
		if ( sf::Keyboard::isKeyPressed( KEY_EXIT) )
		{
			window.close();
			break;
		}

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Left) )
		{
			camera.move( Vector( -10, 0, 0));
		}

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Right) )
		{
			camera.move( Vector( 10, 0, 0));
		}

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Up) )
		{
			camera.move( Vector( 0, 0, 10));
		}

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Down) )
		{
			camera.move( Vector( 0, 0, -10));
		}

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::U) )
		{
			camera.move( Vector( 0, -10, 0));
		}

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::D) )
		{
			camera.move( Vector( 0, 10, 0));
		}

		scene.render( camera);
		scene.draw  ( window);
		window.display();

		// camera.coords( camera.coords() +  Vector( 5, 5, 5));
	}
	
	return 0;
}

