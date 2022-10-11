#include <stdio.h>
#include <float.h>

#include "../include/window.h"
#include "../include/ray.h"
#include "../utils/quadratic.h"


static constexpr float REVERSE_FOV = 0.002f;


Ray::Ray():
	origin_      (),
	dir_         (),
	intersection_(),
	sphere_      ( NULL)
{}

Ray::Ray( const Vector &origin, const Vector &dir):
	origin_      ( origin),
	dir_         ( dir),
	intersection_(),
	sphere_      ( NULL)

{}

Ray::Ray( const Ray &ray):
	origin_      ( ray.origin_),
	dir_         ( ray.dir_),
	intersection_( ray.intersection_),
	sphere_      ( ray.sphere_)
{}


Ray::~Ray()
{}


const Vector &Ray::get_origin() const { return origin_; }
const Vector &Ray::get_dir()    const { return dir_;    }

void Ray::set_origin( const Vector &origin) { origin_ = origin; }
void Ray::set_dir   ( const Vector &dir)    { dir_    = dir;    }


bool          Ray::infinity() const { return sphere_ == NULL; }
const Sphere &Ray::reached()  const { return *sphere_; }

Ray Ray::reflect() const
{
	Ray refl_ray = {};

	Vector incident = dir_.normalize();
	Vector normal   = (intersection_ - sphere_->get_coords()).normalize();

	refl_ray.origin_ = intersection_; 
	refl_ray.dir_    = incident - (2 * (incident & normal)) * normal;

	return refl_ray;
}


void Ray::reach( const std::vector<Sphere> &spheres, const Sphere *const sphere)
{
	float min_distance = FLT_MAX;

	for ( uint32_t i = 0; i < spheres.size(); i++ )
	{
		const Sphere &sphere = spheres[i];
		const float   radius = sphere.get_radius(); 
		const Vector  tmp    = origin_ - sphere.get_coords();

		const float a = (dir_ & dir_);
	       	const float b = 2 * (dir_ & tmp);
		const float c = (tmp & tmp) - (radius * radius);

		QuadraticRoots roots = { 0 };

		solveQuadratic( a, b, c, &roots);
		if ( roots.numberOfRoots >= 1 && min_distance > roots.x1 )
		{
			min_distance = roots.x1;
			sphere_      = &sphere;
		}
	}

	if ( sphere_ == sphere )
	{
		intersection_ = origin_ + dir_ * min_distance; 
	}
}

void Ray::intersect( const std::vector<Sphere> &spheres)
{
	float min_distance = FLT_MAX;

	for ( uint32_t i = 0; i < spheres.size(); i++ )
	{
		const Sphere &sphere = spheres[i];
		const float   radius = sphere.get_radius(); 
		const Vector  tmp    = origin_ - sphere.get_coords();

		const float a = (dir_ & dir_);
	       	const float b = 2 * (dir_ & tmp);
		const float c = (tmp & tmp) - (radius * radius);

		QuadraticRoots roots = { 0 };

		solveQuadratic( a, b, c, &roots);
		if ( roots.numberOfRoots >= 1 && min_distance > roots.x1 )
		{
			min_distance = roots.x1;
			sphere_      = &sphere;
		}
	}

	if ( sphere_ != NULL )
	{
		intersection_ = origin_ + dir_ * min_distance; 
	}
}


void Ray::print() const
{
	printf( "-v- Ray -v-\n"
		"P: %p \n",
		this);

	origin_.print();
	   dir_.print();
	
	printf( "-^- Ray -^-\n");
}
