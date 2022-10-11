#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../include/vector.h"
#include "../include/render.h"
#include "../include/window.h"
#include "../include/common.h"


static const Vector VIEW_COORDS = { 0, 0, -500 };

static       Vector    LIGHT_COORDS = { 900, 900, -1500 }; 
static const sf::Uint8 LIGHT_RGB[3] = { 255, 255,  255  };

static const sf::Uint8 WHITE_RGB[3] = { 255, 255, 255 };

static const float AMBIENT_COEF  = 0.04f;
static const float DIFFUSE_COEF  = 0.3f;
static const float SPECULAR_COEF = 0.1f;


static sf::Uint8 calc_channel( const sf::Uint8 channel_value, const sf::Uint8 light, 
			       const sf::Uint8 material, const float coef)
{
	const sf::Uint8 channel_new_value = channel_value + (light * material * coef) / 255;

	if ( channel_new_value < channel_value )
		return 255;
	
	return channel_new_value;
}

static void calc_channels( sf::Uint8 rgba[4], const sf::Uint8 material[3], const float coef)
{
	rgba[0] = calc_channel( rgba[0], LIGHT_RGB[0], material[0], coef);
	rgba[1] = calc_channel( rgba[1], LIGHT_RGB[1], material[1], coef);
	rgba[2] = calc_channel( rgba[2], LIGHT_RGB[2], material[2], coef);
}

static void light_ambient( sf::Uint8 rgba[4], const sf::Uint8 material[3])
{
	calc_channels( rgba, material, AMBIENT_COEF);
}

static void light_diffuse( sf::Uint8 rgba[4], const sf::Uint8 material[3], Vector &coords)
{
	Vector incident = LIGHT_COORDS - coords;
	const float diffuse_coef = coords.cos( incident) * DIFFUSE_COEF;

	if ( diffuse_coef < 0.f )
		return;
	
	calc_channels( rgba, material, diffuse_coef);
}

static void light_specular( sf::Uint8 rgba[4], Vector &coords)
{
	Vector view      = (VIEW_COORDS  - coords).normalize();	
	Vector incident  = (LIGHT_COORDS - coords).normalize();
	Vector normal    = coords.normalize();
	Vector reflected = normal * (2 * (incident & normal)) - incident;

	const float cos = view.cos( reflected);

	if ( cos < 0.f )
		return;

	const float specular_coef = pow( cos, 25) * SPECULAR_COEF;

	calc_channels( rgba, WHITE_RGB, specular_coef);
}

static void render_pixel( sf::Uint8 rgba[4], Vector &coords)
{
	const sf::Uint8 material[3] = { 255, 255, 70 };

	light_ambient ( rgba, material        );
	light_diffuse ( rgba, material, coords);
	light_specular( rgba,           coords);
}

Vector get_ray( const uint32_t x, const uint32_t y)
{
	return Vector( camera.get_x() - WINDOW_WIDTH  / 2 + x, 
		       camera.get_y() - WINDOW_HEIGHT / 2 + y, 
		      -camera.get_z());
}

bool intersect_sphere( const Vector &ray, const Sphere &sphere, Vector &intersection)
{
	const float  radius = sphere.radius;
	const Vector tmp    = camera - sphere.center;

	QuadraticRoots roots = { 0 };

	solveQuadratic( (ray & ray), 2 * (ray & tmp), (tmp & tmp) + radius * radius, &roots);
	if ( roots.numberOfRoots >= 1)
	{
		intersaction = camera + ray * roots.x1;
		
		return true;
	}
	
	return false;
}

void render( sf::RenderWindow &window, Sphere &sphere)
{
	window.clear( COLOR_BG);

	LIGHT_COORDS.set_x( LIGHT_COORDS.get_x() - 5);
	LIGHT_COORDS.set_y( LIGHT_COORDS.get_y() - 5);
	LIGHT_COORDS.set_z( LIGHT_COORDS.get_z() + 5);

	for ( unsigned pixel_y = 0; pixel_y < WINDOW_HEIGHT; pixel_y++ )
	{
		for ( unsigned pixel_x = 0; pixel_x < WINDOW_WIDTH; pixel_x++ )
		{
			if ( Sphere::is_sphere_pixel( pixel_x, pixel_y) )
			{
				sf::Uint8 rgba[4] = { 0, 0, 0, 255 };

				render_pixel( rgba, sphere.get_coords( pixel_x, pixel_y));
				sphere.set_pixel( pixel_x, pixel_y, rgba);
			}
		}
	}

	sphere.draw( window);
	window.display();
}
