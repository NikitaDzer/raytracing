#ifndef MATERIAL_H
#define MATERIAL_H


#include "color.h"


class Material
{
    private:
	Color color_;
	float albedo_;


    public:
	Material();
	Material( const Color &color, const float albedo);
	Material( const Material &material);

	~Material();


	const Color &color()  const;
	const float &albedo() const;

	void color ( const Color &color);
	void albedo( const float albedo);

	
	void print() const;
};


#endif // MATERIAL_H
