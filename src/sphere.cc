#include <math.h>
#include <string.h>

#include "../include/common.h"
#include "../include/sphere.h"
#include "../utils/quadratic.h"


Sphere::Sphere():
	coords_  (),
	material_(),
	radius_  ( SPHERE_DEFAULT_RADIUS)
{}

Sphere::Sphere( const Vector &coords, const Color &material, const float radius):
	coords_  ( coords),
	material_( material),
	radius_  ( radius)
{}

Sphere::Sphere( const Sphere &sphere):
	coords_  ( sphere.coords_),
	material_( sphere.material_),
	radius_  ( sphere.radius_)
{}

Sphere::~Sphere()
{}


const Vector &Sphere::get_coords()   const { return coords_;   }
const Color  &Sphere::get_material() const { return material_; }
      float   Sphere::get_radius()   const { return radius_;   }

void Sphere::set_coords  ( const Vector &coords)   { coords_   = coords;   }
void Sphere::set_material( const Color  &material) { material_ = material; }
void Sphere::set_radius  ( const float   radius)   { radius_   = radius;   }


bool Sphere::intersect( const Ray &ray, Ray &refl_ray) const 
{
	const Vector ray_origin = ray.get_origin();
	const Vector ray_dir    = ray.get_dir();
	
	const Vector coords = coords_;
	const float  radius = radius_;
	
	const Vector tmp = ray_origin - coords;

	QuadraticRoots roots = { 0 };

	solveQuadratic( (ray_dir & ray_dir), 2 * (ray_dir & tmp), (tmp & tmp) - (radius * radius), &roots);
	if ( roots.numberOfRoots >= 1 && roots.x1 > 0.f)
	{
		Vector intersection = ray_origin + ray_dir * roots.x1;
		Vector incident     = ray_dir.normalize();
		Vector normal       = (intersection - coords).normalize();
		Vector reflected    = incident - (2 * (incident & normal)) * normal;

		refl_ray.set_origin( intersection);
		refl_ray.set_dir   ( reflected);

		return true;
	}

	return false;
}


void Sphere::print() const
{
	printf( "-v- Sphere -v-\n"
		"P: %p\n",
		this);

	  coords_.print();
	material_.print();

	printf( "Radius: %lg\n"
		"-^- Sphere -^-\n",
		radius_);
}
