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


const Vector &Light::get_origin() const { return origin_; }
const Color  &Light::get_color()  const { return color_;  }

void Light::set_origin( const Vector &origin) { origin_ = origin; }
void Light::set_color ( const Color  &color)  { color_  = color;  }


Ray Light::emit( const Vector &coords) const
{
	return Ray( origin_, coords - origin_, color_);
}

Color Light::colorize( const Ray &ray, const std::vector<Sphere> &spheres) const
{
	const Sphere &sphere = ray.reached();

	Color color     = { 0, 0, 0 };
	Ray   light_ray = emit( ray.intersection());
	
	light_ray.reach( &sphere,  spheres);
	
	if ( !light_ray.infinite() && light_ray.intersection() == ray.intersection() )
	{	
		const Vector normal   = ray.intersection() - sphere.get_coords();
		const float  diff_cos = (-1) * light_ray.dir().cos( normal);
	
		if ( diff_cos > 0.f )
		{
			color += Color::calc_color( get_color(), sphere.get_material(), 0.5f * diff_cos);
		}


		const float spec_cos = (-1) * light_ray.dir().cos( ray.reflect().dir());
		
		if ( spec_cos > 0.f )
		{
			color += get_color() * 0.3f * pow( spec_cos, 30);
		}

		color += Color::calc_color( get_color(), sphere.get_material(), 0.01f);
	}

	return color;
}

