#include <stdlib.h>
#include <math.h>

#include "../include/common.h"
#include "../include/window.h"
#include "../include/scene.h"


Scene::Scene():
	pixels_ ( NULL),
	texture_(),
	sprite_ (),

	light_(),
	spheres_()
{	
	pixels_ = (sf::Uint8 *)calloc( WINDOW_WIDTH * WINDOW_HEIGHT * N_RGBA_ELEMS, sizeof(sf::Uint8));

	if ( pixels_ == NULL )
	{
		return;
	}

	texture_.create( WINDOW_WIDTH, WINDOW_HEIGHT);
	sprite_.setTexture( texture_);

	light_.set_origin( Vector( -500, -500, -500));
	light_.set_color ( Color ( 255, 255,  255));

	spheres_.push_back( Sphere( Vector(  0, 0,  50), Color( 255,   0, 255),     50.f));
	spheres_.push_back( Sphere( Vector(  0, 0,  300), Color( 255, 255, 255),  200.f));
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
			Color color = { 10, 10, 10 };
			
			ray.intersect( spheres_);

			if ( !ray.infinity() )
			{	
				
				const Sphere &sphere    = ray.reached();
				      Ray     refl_ray  = ray.reflect();
				      Ray     light_ray = light_.emit( refl_ray.get_origin());
				
				light_ray.reach( spheres_, &sphere);

				
				if ( !light_ray.infinity() && light_ray.reflect().get_origin() != refl_ray.get_origin() )
				{
					color = Color( 0, 0, 0);
				}
				else
				{
					color = Color( 0, 0, 0);

					const float diff_cos = (-1) * (light_ray.get_dir().normalize() & (refl_ray.get_origin() - sphere.get_coords()).normalize());
					if ( diff_cos > 0 )
					{
						color += Color::calc_color( light_.get_color(), sphere.get_material(), 0.3f * diff_cos);
					}
					
					const float spec_cos = (-1) * (light_ray.get_dir().normalize() & refl_ray.get_dir().normalize());
					if ( spec_cos > 0 )
					{
						color += light_.get_color() * 0.3f * pow( spec_cos, 20);
					}
				}	
			}

			set_pixel( x, y, color);	
		}
	}

	light_.set_origin( light_.get_origin() + Vector( 10, 10, 0));

	texture_.update( pixels_);
}


void Scene::draw( sf::RenderWindow &window)
{
	window.draw( sprite_);
}

void Scene::print() const
{

}
