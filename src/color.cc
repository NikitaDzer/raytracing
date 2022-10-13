#include <stdio.h>

#include "../include/color.h"


Color::Color():
	rgb_()
{
	rgb_[0] = 0;
	rgb_[1] = 0;
	rgb_[2] = 0;
}

Color::Color( const uint8_t r, const uint8_t g, const uint8_t b):
	rgb_()
{
	rgb_[0] = r;
	rgb_[1] = g;
	rgb_[2] = b;
}

Color::Color( const Color &color):
	rgb_()
{
	rgb_[0] = color.rgb_[0];
	rgb_[1] = color.rgb_[1];
	rgb_[2] = color.rgb_[2];
}

Color::~Color()
{}


uint8_t Color::get_red()   const { return rgb_[0]; }
uint8_t Color::get_green() const { return rgb_[1]; }
uint8_t Color::get_blue()  const { return rgb_[2]; }


Color Color::operator + ( const Color &color) const
{
	Color sum = {};

	for ( uint8_t i = 0; i < N_RGB_ELEMS; i++ )
	{
		uint16_t sum_channel = this->rgb_[i] + color.rgb_[i];
		
		if ( sum_channel > 255 )
		{
			sum_channel = 255;
		}

		sum.rgb_[i] = sum_channel;
	}

	return sum;
}

Color &Color::operator += ( const Color &color) 
{
	*this = *this + color;

	return *this;
}

Color &Color::operator *= ( const float fac)
{
	return *this = *this * fac;
}


void Color::print() const
{
	printf( "-- Color --\n"
		"P: %p \n"
		"r: %u \n"
		"g: %u \n"
		"b: %u \n"
		"------\n",
		this, this->rgb_[0], this->rgb_[1], this->rgb_[2]);
}



Color operator * ( const Color &color, const float fac)
{
	return Color( color.get_red()   * fac, 
		      color.get_green() * fac, 
		      color.get_blue()  * fac);
}

Color operator * ( const float fac, const Color &color)
{
	return color * fac;
}


Color Color::calc_color( const Color &light, const Color &material, const float coef)
{
	Color color = {};

	for ( uint8_t i = 0; i < N_RGB_ELEMS; i++ )
	{
		color.rgb_[i] = (float)light.rgb_[i] * (float)material.rgb_[i] * coef / 250.f;
	}

	return color;
}
