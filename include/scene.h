#ifndef SCENE_H
#define SCENE_H


#include <stdint.h>

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "sphere.h"
#include "camera.h"
#include "light.h"
#include "color.h"


class Scene
{
    private:
	sf::Uint8   *pixels_;
	sf::Texture  texture_;
	sf::Sprite   sprite_;
	    
	std::vector<Light>  lights_;
	std::vector<Sphere> spheres_;

	void    set_pixel( const uint32_t x, const uint32_t y, const Color  &color);
	void render_pixel( const uint32_t x, const uint32_t y, const Camera &camera); 


    public:
	Scene();
	~Scene();

	void render( const Camera &camera);
	void draw  ( sf::RenderWindow &window);

	void print() const;
};


#endif // SCENE_H
