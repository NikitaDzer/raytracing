#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <unistd.h>

#include "../include/common.h"
#include "../include/window.h"
#include "../include/scene.h"


Scene::Scene():
	pixels_ ( NULL),
	texture_(),
	sprite_ (),

	lights_(),
	spheres_()
{	
	pixels_ = (sf::Uint8 *)calloc( WINDOW_WIDTH * WINDOW_HEIGHT * N_RGBA_ELEMS, sizeof(sf::Uint8));

	if ( pixels_ == NULL )
	{
		return;
	}

	texture_.create( WINDOW_WIDTH, WINDOW_HEIGHT);
	sprite_.setTexture( texture_);
}

Scene::~Scene()
{
	free( pixels_);
}


void Scene::set_pixel( const uint32_t x, const uint32_t y, const Color &color)
{
	sf::Uint8 *const pixel = pixels_ + (x + y * WINDOW_WIDTH) * N_RGBA_ELEMS;

	pixel[0] = color.get_red();
	pixel[1] = color.get_green();
	pixel[2] = color.get_blue();
	pixel[3] = 255;
}

void Scene::render_pixel( const uint32_t x, const uint32_t y, const Camera &camera)
{
	Color color       = Color( 0, 0, 0);	
	Ray   primary_ray = camera.emit( x, y); 

	color += Ray::primary  ( primary_ray, spheres_, lights_);
	color += Ray::secondary( primary_ray, spheres_, lights_);

	set_pixel( x, y, color);	
}


int Scene::add( const Light &light)
{
	lights_.push_back( light);

	return lights_.end() - lights_.begin();
}

int Scene::add( const Sphere &sphere)
{
	spheres_.push_back( sphere);

	return spheres_.end() - spheres_.begin();
}

Light &Scene::get_light( const int index)
{
	return *(lights_.begin() + index);
}

Sphere &Scene::get_sphere( const int index)
{
	return *(spheres_.begin() + index);
}

void Scene::remove_light( const int index)
{
	lights_.erase( lights_.begin() + index);	
}

void Scene::remove_sphere( const int index)
{
	spheres_.erase( spheres_.begin() + index);
}


void Scene::render( const Camera &camera)
{	
	for ( uint32_t y = 0; y < WINDOW_HEIGHT; y++ )
	{
		for ( uint32_t x = 0; x < WINDOW_WIDTH; x++ )
		{
			render_pixel( x, y, camera);
		}
	}

	texture_.update( pixels_);
}


void Scene::draw( sf::RenderWindow &window)
{
	window.draw( sprite_);
}

void Scene::print() const
{

}
