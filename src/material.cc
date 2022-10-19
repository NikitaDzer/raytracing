#include <assert.h>

#include "../include/material.h"


Material::Material():
	color_ (),
	albedo_( 0)
{}

Material::Material( const Color &color, const float albedo):
	color_ ( color),
	albedo_( albedo)
{}

Material::Material( const Material &material):
	color_ ( material.color_),
	albedo_( material.albedo_)
{}


Material::~Material()
{}


const Color &Material::color()  const { return color_;  }
const float &Material::albedo() const { return albedo_; }

void Material::color ( const Color &color)  { color_  = color;  }
void Material::albedo( const float  albedo) { albedo_ = albedo; }


void Material::print() const
{
	assert(0 && "Unimplemented");
}
