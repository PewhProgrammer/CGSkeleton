#include "fisheye.h"

/*
Reference Implementation from
http://paulbourke.net/dome/fisheye/
*/

namespace rt {
	FisheyeCamera::FisheyeCamera(const Point & center, const Vector & forward, const Vector & up, float aperture)
	{
		this->center = center;
		this->aperture = aperture * 0.5f; 
		this->forward = forward; 
		this->up = up;

		this->spanX = cross(forward, up);
	}
	Ray FisheyeCamera::getPrimaryRay(float x, float y) const
	{
		//float radius = sqrt(sqr(x) + sqr(y));

		double phi = atan2(y,x);
		double theta = sqrt(sqr(x) + sqr(y)) * aperture;

		Vector v1 = sin(theta) * cos(phi) * spanX;
		Vector v2 = sin(theta) * sin(phi) * up; 
		Vector v3 = cos(theta) *            forward; 

		return Ray(center,
			(v1 + v2 + v3).normalize()
		);
	}
}