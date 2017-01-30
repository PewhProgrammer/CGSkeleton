#include "dofperspective.h"

using namespace rt;

rt::DOFPerspectiveCamera::DOFPerspectiveCamera(const Point & center, const Vector & forward, const Vector & up, float verticalOpeningAngle, float horizonalOpeningAngle, float focalDistance, float apertureRadius)
{
	this->center = center;
	this->forward = forward.normalize();
	this->radius = apertureRadius;
	this->focalDistance = focalDistance;

	spanX = cross(this->forward, up).normalize() * tan(horizonalOpeningAngle * 0.5f);
	spanY = cross(this->forward, spanX).normalize() * tan(verticalOpeningAngle * 0.5f);
}

/*mainly from lecture slides*/
Ray rt::DOFPerspectiveCamera::getPrimaryRay(float x, float y) const
{
	float x1, y1, theta,rad;
	//random points on disc in spherical coords
	//float rad = sqrt(radius * random());
	rad = radius * sqrt(random());

	theta = random(0, 2 * pi);
	x1 = rad * cos(theta);
	y1 = rad * sin(theta);

	Point o_prime = center + x1 * spanX.normalize() + y1 * spanY.normalize(); //create point of confusion
	Vector oc = o_prime - center;

	Vector d = forward + x * spanX + y * spanY;

	d = d * focalDistance / dot(focalDistance * forward, d);
	//Point h  
	d = (d - oc).normalize(); // h - o'

	return Ray(o_prime, d);

}
