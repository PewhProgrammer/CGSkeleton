#include "orthographic.h"

/*
Transform 3D View into 2D View 
Instead of perspective viewing frustrum we use a cube
and move the center of the camera
*/

namespace rt {
	OrthographicCamera::OrthographicCamera(const Point & center, const Vector & forward, const Vector & up, float scaleX, float scaleY)
	{
		OrthographicCamera::center = center;

		spanX = scaleX * (cross(-up, forward).normalize()) / 2;
		spanY = scaleY * (-up).normalize() / 2;

		this->dir = cross(spanX, spanY).normalize(); 
	}
	Ray OrthographicCamera::getPrimaryRay(float x, float y) const
	{
		return Ray(center + x *spanX + y*spanY, dir);
	}
}