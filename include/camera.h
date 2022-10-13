#ifndef CAMERA_H
#define CAMERA_H


#include <stdint.h>

#include "vector.h"
#include "ray.h"


class Camera
{
    private:
	Vector coords_;


    public:
	Camera();
	Camera( const Vector &coords);
	Camera( const Camera &camera);

	~Camera();


	const Vector &coords() const;

	void coords( const Vector &coords);	
	void move  ( const Vector &vector);
	
	Ray emit( const uint32_t x, const uint32_t y) const;
};


#endif // CAMERA_H
