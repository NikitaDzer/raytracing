#include "../include/window.h"
#include "../include/camera.h"


static constexpr float REVERSE_FOV = 0.002f;


Camera::Camera():
	coords_()
{}

Camera::Camera( const Vector &coords):
	coords_( coords)
{}

Camera::Camera( const Camera &camera):
	coords_( camera.coords_)
{}


Camera::~Camera()
{}


const Vector &Camera::coords() const { return coords_; }

void Camera::coords( const Vector &coords) { coords_ = coords; }


Ray Camera::emit( const uint32_t x, const uint32_t y) const
{
	const float shift_x = (-1) * (int32_t)(x - WINDOW_WIDTH  / 2) * coords_.get_z() * REVERSE_FOV;
	const float shift_y = (-1) * (int32_t)(y - WINDOW_HEIGHT / 2) * coords_.get_z() * REVERSE_FOV;

	Vector origin = coords_;
	Vector dir    = {};

	dir.set_x( coords_.get_x() + shift_x);
	dir.set_y( coords_.get_y() + shift_y);
	dir.set_z( coords_.get_z() * (-1));

	return Ray( origin, dir);
}
