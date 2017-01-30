#include "ambient.h"

namespace rt {
	AmbientLight::AmbientLight(RGBColor & power)
	{
		intensity = power;
	}
	LightHit AmbientLight::getLightHit(const Point & p) const
	{
		LightHit result; 
		result.distance = 0;
		result.direction = Vector(0, 0, 0);
		return result;
	}
	RGBColor AmbientLight::getIntensity(const LightHit & irr) const
	{
		return intensity;
	}
}