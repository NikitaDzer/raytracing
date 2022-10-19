#ifndef RAY_H
#define RAY_H


#include <stdint.h>

#include <vector>

#include "vector.h"
#include "sphere.h"
#include "light.h"
#include "color.h"


class Light;
class Sphere;

class Ray
{
	class Kernel
	{
	    private:
		Vector origin_;
		Vector dir_;
		Color  color_;
		
	
	     public:
		Kernel( const Vector &origin, const Vector &dir, const Color &color);
		Kernel( const Kernel &kern);

		~Kernel();

		
		const Vector &get_origin() const;
		const Vector &get_dir()    const;
		const Color  &get_color()  const;

		void set_origin( const Vector &origin);
		void set_dir   ( const Vector &dir);
		void set_color ( const Color  &color);		
	};	


    private:
	Kernel kern_;

	Vector        intersection_;
	const Sphere *sphere_;
	

    public:
	Ray();
	Ray( const Vector &origin, const Vector &dir, const Color &color);
	Ray( const Ray &ray);

	~Ray();

	
	const Vector &origin() const;
	const Vector &dir()    const;
	const Color  &color()  const;

	void origin( const Vector &origin);
	void dir   ( const Vector &dir);
	void color ( const Color  &color);

	
	bool          infinite()     const;
	Ray           reflect()      const;
	const Sphere &reached()      const;
	const Vector &intersection() const;

	void reach    ( const Sphere *const sphere, const std::vector<Sphere> &spheres);
	void intersect( const std::vector<Sphere> &spheres);


	void print() const;


	static Color primary  ( Ray &primary_ray, 
				const std::vector<Sphere> &spheres, const std::vector<Light> &lights);
	static Color secondary( const Ray &ray,
				const std::vector<Sphere> &spheres, const std::vector<Light> &lights);
};


#endif // RAY_H
