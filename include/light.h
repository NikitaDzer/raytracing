#ifndef LIGHT_H
#define LIGHT_H


#include "vector.h"
#include "color.h"
#include "ray.h"


class Ray;

class Light
{
    private:
	Vector origin_;
	Color  color_;

    public:
	Light();
	Light( const Vector &origin, const Color &color);
	Light( const Light &light);

	~Light();


	const Vector &get_origin() const;
	const Color  &get_color()  const;

	void set_origin( const Vector &origin);
	void set_color ( const Color  &color);

	
	Ray emit( const Vector &coords) const;
	

	void print() const;
};


#endif // LIGHT_H
