#include "environment.h"

/*
Reference Implementation from
http://paulbourke.net/dome/fisheye/

instead of sphere, we have a elipsis
thats why we cant use unified radius across our computation
*/

namespace rt {

	rt::EnvironmentCamera::EnvironmentCamera(const Point & center, const Vector & forward, 
		const Vector & up, float radiusX, float radiusY)
	{
		this->center = center;
		this->forward = forward;
		this->radiusX = radiusX * 0.5f; 
		this->radiusY = radiusY * 0.5f; 

		this->spanX = cross(forward, up);
		this->up = cross(forward, spanX);
	}

	Ray rt::EnvironmentCamera::getPrimaryRay(float x, float y) const
	{
		double phi = y * radiusY;
		double theta = x * radiusX;

		Vector v1 = sin(theta) * cos(phi) * spanX;
		Vector v2 = sin(theta) * sin(phi) * up;
		Vector v3 = cos(theta) *            forward;

		return Ray(center,
			(v1 + v2 + v3).normalize()
		);
	}
}
