#include <stdio.h>
#include <float.h>

#include "../include/window.h"
#include "../include/common.h"
#include "../include/ray.h"
#include "../utils/quadratic.h"


static constexpr float REVERSE_FOV = 0.002f;


Ray::Kernel::Kernel( const Vector &origin, const Vector &dir, const Color &color):
	origin_( origin),
	dir_   ( dir),
	color_ ( color)
{}

Ray::Kernel::Kernel( const Kernel &kern):
	origin_( kern.origin_),
	dir_   ( kern.dir_),
	color_ ( kern.color_)
{}


Ray::Kernel::~Kernel()
{}


const Vector &Ray::Kernel::get_origin() const { return origin_; }
const Vector &Ray::Kernel::get_dir()    const { return dir_;    }
const Color  &Ray::Kernel::get_color()  const { return color_;  }

void Ray::Kernel::set_origin( const Vector &origin) { origin_ = origin; }
void Ray::Kernel::set_dir   ( const Vector &dir)    { dir_    = dir;    }
void Ray::Kernel::set_color ( const Color  &color)  { color_  = color;  }



Ray::Ray():
	kern_        ( Vector( 0, 0, 0), Vector( 0, 0, 0), Color( 0, 0, 0)),
	intersection_(),
	sphere_      ( NULL)
{}

Ray::Ray( const Vector &origin, const Vector &dir, const Color &color):
	kern_        ( origin, dir.normalize(), color),
	intersection_(),
	sphere_      ( NULL)

{}

Ray::Ray( const Ray &ray):
	kern_        ( ray.kern_),
	intersection_( ray.intersection_),
	sphere_      ( ray.sphere_)
{}


Ray::~Ray()
{}


const Vector &Ray::origin() const { return kern_.get_origin(); }
const Vector &Ray::dir()    const { return kern_.get_dir();    }
const Color  &Ray::color()  const { return kern_.get_color();  }

void Ray::origin( const Vector &origin) { kern_.set_origin( origin);          }
void Ray::dir   ( const Vector &dir)    { kern_.set_dir   ( dir.normalize()); }
void Ray::color ( const Color  &color)  { kern_.set_color ( color);           }


bool          Ray::infinite()     const { return sphere_ == NULL; }
const Sphere &Ray::reached()      const { return *sphere_;        }
const Vector &Ray::intersection() const { return intersection_;   }

Ray Ray::reflect() const
{
	Ray refl_ray = {};

	Vector incident = dir();
	Vector normal   = (intersection_ - sphere_->get_coords()).normalize();
	
	Vector refl_origin = intersection_;
	Vector refl_dir    = incident - (2 * (incident & normal)) * normal;
	Color  refl_color  = Color::calc_color( color(), sphere_->get_material().color(), 1.f);

	refl_ray.origin( refl_origin);
	refl_ray.dir   ( refl_dir);
	refl_ray.color ( refl_color);

	return refl_ray;
}


void Ray::reach( const Sphere *const sphere,  const std::vector<Sphere> &spheres)
{
	float min_distance = FLT_MAX;

	for ( std::vector<Sphere>::const_iterator spheres_it = spheres.begin(); spheres_it != spheres.end(); spheres_it++ )
	{	
		const float   radius = spheres_it->get_radius(); 
		const Vector  tmp    = origin() - spheres_it->get_coords();

		const float a = (dir() & dir());
	       	const float b = 2 * (dir() & tmp);
		const float c = (tmp & tmp) - (radius * radius);

		QuadraticRoots roots = { 0 };

		solveQuadratic( a, b, c, &roots);
		if ( roots.numberOfRoots >= 1 && roots.x1 > 0.f && min_distance > roots.x1 )
		{
			min_distance = roots.x1;
			sphere_      = &(*spheres_it);
		}
	}

	if ( sphere_ == sphere )
	{
		intersection_ = origin() + dir() * min_distance; 
	}
}

void Ray::intersect( const std::vector<Sphere> &spheres)
{
	float min_distance = FLT_MAX;
	
	for ( std::vector<Sphere>::const_iterator spheres_it = spheres.begin(); spheres_it != spheres.end(); spheres_it++ )
	{
		const float   radius = spheres_it->get_radius(); 
		const Vector  tmp    = origin() - spheres_it->get_coords();

		const float a = (dir() & dir());
	       	const float b = 2 * (dir() & tmp);
		const float c = (tmp & tmp) - (radius * radius);

		QuadraticRoots roots = { 0 };

		solveQuadratic( a, b, c, &roots);
		if ( roots.numberOfRoots >= 1 && roots.x1 > 0.f && min_distance > roots.x1 )
		{
			min_distance = roots.x1;
			sphere_      = &(*spheres_it);
		}
	}

	if ( sphere_ != NULL )
	{
		intersection_ = origin() + dir() * min_distance; 
	}
}


void Ray::print() const
{
	/*
	printf( "-v- Ray -v-\n"
		"P: %p \n",
		this);

	origin_.print();
	   dir_.print();
	
	printf( "-^- Ray -^-\n");
	*/
}


Color Ray::primary( Ray &primary_ray, const std::vector<Sphere> &spheres, const std::vector<Light> &lights)
{
	Color color = {};

	primary_ray.intersect( spheres);

	if ( primary_ray.infinite() )
	{
		color = Color( 30, 30, 30);
	}
	else
	{
		color = Color( 0, 0, 0);

		for ( std::vector<Light>::const_iterator light = lights.begin(); light != lights.end(); light++ )
		{
			color += light->colorize( primary_ray, spheres, COLORIZE_FULL);
		}
	}

	return color;
}


Color recursive_secondary( Ray ray, const std::vector<Sphere> &spheres, const std::vector<Light> &lights, const float intensity)
{
	Color color = Color( 0, 0, 0);

	if ( intensity < 0.1f )
	{
		return color;
	}
	
	
	ray.intersect( spheres);

	if ( ray.infinite() )
	{
		return color;
	}

	for ( std::vector<Light>::const_iterator light = lights.begin(); light != lights.end(); light++ )
	{
		color += light->colorize( ray, spheres, COLORIZE_DIFFUSE);
	}

	const float albedo          = ray.reached().get_material().albedo();
	const Color secondary_color = recursive_secondary( ray.reflect(), spheres, lights, intensity * 0.6f);

	color *= 1 - albedo;
	color += Color::calc_color( secondary_color, Color( 255, 255, 255), albedo);

	return color;
}

Color Ray::secondary( const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Light> &lights)
{
	if ( ray.infinite() )
	{
		return Color( 0, 0, 0);
	}


	const float albedo          = ray.reached().get_material().albedo();
	const Color secondary_color = recursive_secondary( ray.reflect(), spheres, lights, 1.0f);

	return Color::calc_color( secondary_color, Color( 255, 255, 255), albedo);
}
