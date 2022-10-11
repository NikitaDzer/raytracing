#include "../include/light.h"


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
	return Ray( origin_, coords - origin_);
}
