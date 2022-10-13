#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "../include/vector.h"


Vector::Kernel::Kernel( const float x, const float y, const float z):
	x_  ( x),
	y_  ( y),
	z_  ( z),
	len_( NAN)
{}

Vector::Kernel::Kernel( const Vector::Kernel &kern):
	x_  ( kern.x_),
	y_  ( kern.y_),
	z_  ( kern.z_),
	len_( kern.len_)
{}

Vector::Kernel::~Kernel()
{
	if ( 0 )
	{	// WTF ( what terrible failure, of course )
		assert( isnan( len_) || ((float)(x_ * x_ + y_ * y_ + z_ * z_) == len_ * len_)); 
	}
}


float Vector::Kernel::get_x()   const { return x_;   }
float Vector::Kernel::get_y()   const { return y_;   }
float Vector::Kernel::get_z()   const { return z_;   }
float Vector::Kernel::get_len() const { return len_; }

void Vector::Kernel::set_x  ( const float x)   { x_ = x; len_ = NAN; }
void Vector::Kernel::set_y  ( const float y)   { y_ = y; len_ = NAN; }
void Vector::Kernel::set_z  ( const float z)   { z_ = z; len_ = NAN; }
void Vector::Kernel::set_len( const float len) {         len_ = len; } 

float Vector::Kernel::calc_len() const
{
	return sqrtf( x_ * x_ + y_ * y_ + z_ * z_);
}


Vector::Vector():
	kern_( 0.f, 0.f, 0.f)
{}

Vector::Vector( const float x, const float y, const float z):
	kern_( x, y, z)
{}

Vector::Vector( const Vector &vec):
	kern_( vec.kern_)
{}

Vector::~Vector()
{}


bool Vector::operator == ( const Vector &vec) const
{
	return    fabs( get_x() - vec.get_x() ) < 0.1f 
	       && fabs( get_y() - vec.get_y() ) < 0.1f 
	       && fabs( get_z() - vec.get_z() ) < 0.1f;
}

bool Vector::operator != ( const Vector &vec) const
{
	return !(*this == vec);
}

Vector Vector::operator + ( const Vector &vec) const
{
	Vector sum = {};

	sum.set_x( get_x() + vec.get_x());
	sum.set_y( get_y() + vec.get_y());
	sum.set_z( get_z() + vec.get_z());

	return sum;
}

Vector Vector::operator - ( const Vector &vec) const
{
	Vector diff = {};

	diff.set_x( get_x() - vec.get_x());
	diff.set_y( get_y() - vec.get_y());
	diff.set_z( get_z() - vec.get_z());	

	return diff;
}

float Vector::operator & ( const Vector &vec) const
{
	float dot_product = 0;

	dot_product += get_x() * vec.get_x();
	dot_product += get_y() * vec.get_y();
	dot_product += get_z() * vec.get_z();

	return dot_product;
}

Vector Vector::operator ^ ( const Vector &vec) const
{
	Vector cross_product = {};

	const float x1 = get_x();
	const float y1 = get_y();
	const float z1 = get_z();

	const float x2 = vec.get_x();
	const float y2 = vec.get_y();
	const float z2 = vec.get_z();

	cross_product.set_x( y1 * z2 - z1 * y2);
	cross_product.set_y( z1 * x2 - x1 * z2);
	cross_product.set_z( x1 * y2 - y1 * x2);

	return cross_product;	
}

Vector &Vector::operator += ( const Vector &vec)
{
	set_x( get_x() + vec.get_x());
	set_y( get_y() + vec.get_y());
	set_z( get_z() + vec.get_z());

	return *this;
}

Vector &Vector::operator -= ( const Vector &vec)
{
	set_x( get_x() - vec.get_x());
	set_y( get_y() - vec.get_y());
	set_z( get_z() - vec.get_z());

	return *this;
}

Vector &Vector::operator *= ( const float factor)
{
	set_x( get_x() * factor);
	set_y( get_y() * factor);
	set_z( get_z() * factor);

	return *this;
}


float Vector::get_x() const { return kern_.get_x(); }
float Vector::get_y() const { return kern_.get_y(); }
float Vector::get_z() const { return kern_.get_z(); }

float Vector::get_len() 
{ 
	if ( isnan( kern_.get_len()) ) 
	{ 
		kern_.set_len( kern_.calc_len()); 
	}

	return kern_.get_len();
}


void Vector::set_x( const float x) { kern_.set_x( x); }
void Vector::set_y( const float y) { kern_.set_y( y); }
void Vector::set_z( const float z) { kern_.set_z( z); }
	
void Vector::set( const float x, const float y, const float z)
{
	set_x( x); 
	set_y( y); 
	set_z( z);
}


float Vector::cos( const Vector &vector) const
{
	float len1 = 0.f;
	float len2 = 0.f;

	if ( isnan( kern_.get_len()) )
	{
		len1 = kern_.calc_len();
	}
	else
	{
		len1 = kern_.get_len();
	}

	if ( isnan( vector.kern_.get_len()) )
	{
		len2 = vector.kern_.calc_len(); 
	}
	else
	{
		len2 = vector.kern_.get_len();
	}

	return (*this & vector) / (len1 * len2);
}

Vector Vector::normalize() const
{
	const float  len        = kern_.calc_len();
	      Vector normalized = {};

	normalized.set_x( get_x() / len);
	normalized.set_y( get_y() / len);
	normalized.set_z( get_z() / len);

	normalized.get_len();
	
	return normalized;
}


void Vector::print() const
{
	printf(	"-- Vector --\n"
		"P: %p  \n"
		"x: %lg \n"
		"y: %lg \n"
		"z: %lg \n"
		"L: %lg \n"
		"-------\n",
		this, get_x(), get_y(), get_z(), kern_.get_len());
}


static Vector calc_product( const Vector &vec, const float fac)
{
	Vector product = {};

	product.set_x( vec.get_x() * fac);
	product.set_y( vec.get_y() * fac);
	product.set_z( vec.get_z() * fac);

	return product;
}

Vector operator * ( const Vector &vec, const float fac)
{
	return calc_product( vec, fac);
}

Vector operator * ( const float fac, const Vector &vec)
{
	return calc_product( vec, fac);
}
