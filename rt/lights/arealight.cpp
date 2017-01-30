#include "arealight.h"

namespace rt {
	rt::AreaLight::AreaLight(Solid * source)
	{
		this->src = source;
	}

	LightHit rt::AreaLight::getLightHit(const Point & p) const
	{
		LightHit result;
		Vector dir = src->sample() - p;

		result.distance = dir.length() - 0.001f; //factor for precision problem
		result.direction = dir.normalize();

		return result;
	}

	RGBColor rt::AreaLight::getIntensity(const LightHit & irr) const
	{
		/*getEmission call with dummy values as arguments*/ 
		/*computing radiance*/
		return src->material->getEmission(Point(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0))  * src->getArea() / sqr(irr.distance);
	}
}
