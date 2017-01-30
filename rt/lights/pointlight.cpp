#include "pointlight.h"

namespace rt {
	PointLight::PointLight(const Point & position, const RGBColor & intensity)
	{
		pos = position;
		this->intensity = intensity;
	}
	LightHit PointLight::getLightHit(const Point & p) const
	{
		LightHit result; 
		Vector dir = pos - p;
		
		result.distance = dir.length();
		result.direction = dir.normalize();

		return result;
	}
	RGBColor PointLight::getIntensity(const LightHit & irr) const
	{
		return intensity / sqr(irr.distance);
	}
}