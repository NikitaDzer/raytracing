#ifndef COLOR_H
#define COLOR_H


#include <stdint.h>


static constexpr uint32_t N_RGB_ELEMS = 3;
static constexpr uint32_t N_RGBA_ELEMS = 4;


class Color
{
    private:
	uint8_t rgb_[N_RGB_ELEMS];


    public:
	Color();
	Color( const uint8_t r, const uint8_t g, const uint8_t b);
	Color( const Color &color);

	~Color();

	
	Color  operator +  ( const Color &color) const;
	
	Color &operator += ( const Color &color);
	Color &operator *= ( const float  fac);

	uint8_t get_red()   const;
	uint8_t get_green() const;
	uint8_t get_blue()  const;


	void print() const;


	static Color calc_color( const Color &light, const Color &material, const float coef);	
};


Color operator * ( const Color &color, const float  fac);
Color operator * ( const float  fac,   const Color &color);	

#endif // COLOR_H
