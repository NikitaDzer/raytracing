#ifndef RAY_H
#define RAY_H


#include <stdint.h>

#include <vector>

#include "vector.h"
#include "sphere.h"


class Sphere;

class Ray
{
    private:
	Vector origin_;
	Vector dir_;
	Vector intersection_;
	
	const Sphere *sphere_;
	


    public:
	Ray();
	Ray( const Vector &origin, const Vector &dir);
	Ray( const Ray &ray);

	~Ray();

	
	const Vector &get_origin() const;
	const Vector &get_dir()    const;

	void set_origin( const Vector &origin);
	void set_dir   ( const Vector &dir);
	
	
	bool          infinity() const;
	Ray           reflect()  const;
	const Sphere &reached()  const;
	
	void reach    ( const std::vector<Sphere> &spheres, const Sphere *const sphere);
	void intersect( const std::vector<Sphere> &spheres);


	void print() const;
};


#endif // RAY_H
