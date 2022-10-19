#include <math.h>

#include "../include/light.h"
#include "../include/common.h"


Light::Light():
	origin_(),
	color_ ()
{}

Light::Light( const Vector &origin, const Color &color):
	origin_( origin),
	color_ ( color)
{}

Light::Light( const Light &light):
	origin_( light.origin_),
	color_ ( light.color_)
{}


Light::~Light()
{}


Color Light::colorize_diffuse( const Ray &ray, const Ray &light_ray, const Sphere &sphere) const
{
	Color color = Color( 0, 0, 0);

	const Vector normal   = ray.intersection() - sphere.get_coords();
	const float  diff_cos = (-1) * light_ray.dir().cos( normal);
	
	if ( diff_cos > 0.f )
	{
		color = Color::calc_color( get_color(), (1 - sphere.get_material().albedo()) * sphere.get_material().color(), 0.6f * diff_cos);
	}

	return color;
}

Color Light::colorize_specular( const Ray &ray, const Ray &light_ray, const Sphere &sphere) const
{
	Color color = Color( 0, 0, 0);

	const float spec_cos = (-1) * light_ray.dir().cos( ray.reflect().dir());
		
	if ( spec_cos > 0.f )
	{
		color = (1 - sphere.get_material().albedo()) * get_color() * 0.4f * pow( spec_cos, 30);
	}

	return color;
}


const Vector &Light::get_origin() const { return origin_; }
const Color  &Light::get_color()  const { return color_;  }

void Light::set_origin( const Vector &origin) { origin_ = origin; }
void Light::set_color ( const Color  &color)  { color_  = color;  }


Ray Light::emit( const Vector &coords) const
{
	return Ray( origin_, coords - origin_, color_);
}

Color Light::colorize( const Ray &ray, const std::vector<Sphere> &spheres, const ColorizeType colorize_type) const
{
	const Sphere &sphere = ray.reached();

	Color color     = { 0, 0, 0 };
	Ray   light_ray = emit( ray.intersection());
	
	light_ray.reach( &sphere,  spheres);
	
	if ( !light_ray.infinite() && light_ray.intersection() == ray.intersection() )
	{
		color = colorize_diffuse( ray, light_ray, sphere);
		
		if ( colorize_type == COLORIZE_FULL )
		{
			color += colorize_specular( ray, light_ray, sphere);
		}
	}

	return color;
}

