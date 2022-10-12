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

	lights_.push_back( Light( Vector( -300, -100, -500), Color( 255, 255, 255)));
	lights_.push_back( Light( Vector( -500,  300, -500), Color( 255, 255, 255)));

	spheres_.push_back( Sphere( Vector( 0, 0,  50), Color( 255,   0, 255),   50.f));
	spheres_.push_back( Sphere( Vector( 0, 0, 300), Color( 255, 255, 255),  200.f));
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


void Scene::render( const Camera &camera, sf::RenderWindow &window)
{	
	for ( uint32_t y = 0; y < WINDOW_HEIGHT; y++ )
	{
		for ( uint32_t x = 0; x < WINDOW_WIDTH; x++ )
		{
			Ray ray = camera.emit( x, y);
			Color color = { 0, 0, 0 };
			
			ray.intersect( spheres_);

			if ( ray.infinite() )
			{
				color = Color( 10, 10, 10);
			}
			else
			{
				const Sphere &sphere       = ray.reached();
				      Ray     refl_ray     = ray.reflect();

				for ( uint32_t i = 0; i < lights_.size(); i++ )
				{
					Light &light     = lights_[i];
					Ray    light_ray = light.emit( ray.intersection());

					light_ray.reach( spheres_, &sphere);
					
					if ( !light_ray.infinite() && light_ray.intersection() == ray.intersection() )
					{	
						
						const float diff_cos = (-1) * (light_ray.dir() & (ray.intersection() - sphere.get_coords()).normalize());
						if ( diff_cos > 0 )
						{
							color += Color::calc_color( light.get_color(), sphere.get_material(), 0.3f * diff_cos);
						}
							
						const float spec_cos = (-1) * (light_ray.dir() & refl_ray.dir());
						if ( spec_cos > 0 )
						{
							color += light.get_color() * 0.3f * pow( spec_cos, 20);
						}
					
					}
				}
			}

			set_pixel( x, y, color);	
		}
	}

	lights_[0].set_origin( lights_[0].get_origin() + Vector( 10, 10, 0));

	

	texture_.update( pixels_);
}


void Scene::draw( sf::RenderWindow &window)
{
	window.draw( sprite_);
}

void Scene::print() const
{

}
