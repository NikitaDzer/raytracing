#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string.h>
#include <unistd.h>

#include "include/window.h"
#include "include/vector.h"
#include "include/common.h"
#include "include/scene.h"


int main()
{
	sf::RenderWindow window = {};
	init_window( window);

	Camera camera = Vector( 0, 0, -300);
	Scene  scene  = {};


	scene.add( Light( Vector( 500, 0, -500), Color( 255, 255, 255)));
	scene.add( Light( Vector(-500, 0, -500), Color( 255, 255, 255)));

	scene.add( Sphere( Vector( 0, -50, 300), Material( Color( 255, 255, 255), 0.9f), 200.f));
	scene.add( Sphere( Vector( 0, 200, 100), Material( Color( 255, 255,   0), 0.0f), 100.f));


	while ( window.isOpen() )
    	{	
		if ( sf::Keyboard::isKeyPressed( KEY_EXIT) )
		{
			window.close();
			break;
		}

		Camera::handle_keyboard( camera);

		scene.render( camera);
		scene.draw  ( window);
		window.display();
	}
	
	return 0;
}

