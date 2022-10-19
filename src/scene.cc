#include <stdlib.h>
#include <math.h>

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
	
	
	lights_.push_back( Light( Vector( 200, 100, -300), Color( 255, 255, 255)));

	spheres_.push_back( Sphere( Vector(  200,    0,  300), Material( Color( 255, 255, 255), 0.1f), 200.f));
	spheres_.push_back( Sphere( Vector( -200,    0,  300), Material( Color( 255, 255, 255), 0.1f), 200.f));

	spheres_.push_back( Sphere( Vector(  0, 100,  100), Material( Color( 0, 255, 255), 0.0f), 50.f));
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


/* 
 *
 * ray.reach( spheres);
 * 
 * if ( !ray.infinity() )
 * {
 *	sphere   = ray.reached();
 *	refl_ray = ray.reflect();
 *	
 *
 * }	
 *
 */


void Scene::render( const Camera &camera)
{	
	for ( uint32_t y = 0; y < WINDOW_HEIGHT; y++ )
	{
		for ( uint32_t x = 0; x < WINDOW_WIDTH; x++ )
		{
			render_pixel( x, y, camera);
		}
	}

	//lights_[0].set_origin( lights_[0].get_origin() + Vector( 10, 10, 0));

	texture_.update( pixels_);
}


void Scene::draw( sf::RenderWindow &window)
{
	window.draw( sprite_);
}

void Scene::print() const
{

}
