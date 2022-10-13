#include <stdio.h>
#include <float.h>

#include "../include/window.h"
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
	Color  refl_color  = Color::calc_color( color(), sphere_->get_material(), 1.f);

	refl_ray.origin( refl_origin);
	refl_ray.dir   ( refl_dir);
	refl_ray.color ( refl_color);

	return refl_ray;
}


void Ray::reach( const Sphere *const sphere,  const std::vector<Sphere> &spheres)
{
	float min_distance = FLT_MAX;

	for ( uint32_t i = 0; i < spheres.size(); i++ )
	{
		const Sphere &sphere = spheres[i];
		const float   radius = sphere.get_radius(); 
		const Vector  tmp    = origin() - sphere.get_coords();

		const float a = (dir() & dir());
	       	const float b = 2 * (dir() & tmp);
		const float c = (tmp & tmp) - (radius * radius);

		QuadraticRoots roots = { 0 };

		solveQuadratic( a, b, c, &roots);
		if ( roots.numberOfRoots >= 1 && roots.x1 > 0.f && min_distance > roots.x1 )
		{
			min_distance = roots.x1;
			sphere_      = &sphere;
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

	for ( uint32_t i = 0; i < spheres.size(); i++ )
	{
		const Sphere &sphere = spheres[i];
		const float   radius = sphere.get_radius(); 
		const Vector  tmp    = origin() - sphere.get_coords();

		const float a = (dir() & dir());
	       	const float b = 2 * (dir() & tmp);
		const float c = (tmp & tmp) - (radius * radius);

		QuadraticRoots roots = { 0 };

		solveQuadratic( a, b, c, &roots);
		if ( roots.numberOfRoots >= 1 && roots.x1 > 0.f && min_distance > roots.x1 )
		{
			min_distance = roots.x1;
			sphere_      = &sphere;
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
