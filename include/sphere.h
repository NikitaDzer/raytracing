#ifndef SPHERE_H
#define SPHERE_H


#include <stdio.h>

#include "material.h"
#include "vector.h"
#include "ray.h"


static constexpr float SPHERE_DEFAULT_RADIUS = 10.f;


class Ray;

class Sphere
{
    private:
	Vector   coords_;		
	Material material_;
	float    radius_;

    public:
	Sphere();
	Sphere( const Vector &coords, const Material &material, const float radius);
	Sphere( const Sphere &sphere);

	~Sphere();

	
	const Vector   &get_coords()   const;	
	const Material &get_material() const;
	const float    &get_radius()   const;

	void set_coords  ( const Vector   &coords);
	void set_material( const Material &material);
	void set_radius  ( const float     radius);

	
	bool intersect( const Ray &ray, Ray &refl_ray) const;


	void print() const;
};


#endif // SPHERE_H
