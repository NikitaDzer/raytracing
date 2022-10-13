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

	//lights_.push_back( Light( Vector( -50, 0, -100), Color( 255, 255, 255)));
	//lights_.push_back( Light( Vector(  50, 0, -100), Color( 255, 255, 255)));
	//lights_.push_back( Light( Vector( 0, 0,    0), Color( 255, 255, 255)));
	//lights_.push_back( Light( Vector( -500,  300, -500), Color( 255, 255, 255)));
	lights_.push_back( Light( Vector(  0,  0, -200), Color( 255, 255, 255)));
	//lights_.push_back( Light( Vector( 1000, 1000, -700), Color( 255, 255, 255))); 

	spheres_.push_back( Sphere( Vector(  0, 0,     320), Color( 255, 255, 255), 200.f));
	//spheres_.push_back( Sphere( Vector( -100, 0,   50), Color( 255, 0, 255),  50.f));
	spheres_.push_back( Sphere( Vector(  100, 0, 50), Color(   0, 255, 255),  50.f));
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
	Color color       = {};	
	Ray   primary_ray = camera.emit( x, y); 

	primary_ray.intersect( spheres_);

	if ( primary_ray.infinite() )
	{
		color = Color( 30, 30, 30);
	}
	else
	{
		color = Color( 0, 0, 0);

		for ( uint32_t i = 0; i < lights_.size(); i++ )
		{
			color += lights_[i].colorize( primary_ray, spheres_);
		}


		float intensity = 0.5f; 
		Ray   ray       = primary_ray.reflect();
		
		while ( true )
		{
			Color add_color = { 0, 0, 0 };

			ray.intersect( spheres_);

			if ( ray.infinite() )
			{
				break;
			}

			for ( uint32_t i = 0; i < lights_.size(); i++ )
			{
				add_color += Color::calc_color( lights_[i].colorize( ray, spheres_), primary_ray.reached().get_material(), intensity);
			}

			color += add_color;
			ray    = ray.reflect();

			intensity *= 0.5f;

			if ( intensity < 0.1f )
			{
				break;
			}
		}
	
	}
	/*
	while ( true )
	{
		Color add_color = { 0, 0, 0 };

		ray.intersect( spheres_);

		if ( ray.infinite() )
		{
			break;
		}
			
		for ( uint32_t i = 0; i< lights_.size(); i++ )
		{
			add_color += lights_[i].colorize( ray, spheres_);
		}	

		color += add_color * intensity;
		ray    = ray.reflect();
		
		intensity *= 0.1f;
		
		if ( intensity < 0.1f )
		{
			break;
		}
	}
	*/

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
