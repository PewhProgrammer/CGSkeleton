#include "directional.h"

namespace rt {
	DirectionalLight::DirectionalLight(const Vector & direction, const RGBColor & color)
	{
		this->color = color;

		LightHit result;
		result.direction = -direction;
		result.distance = FLT_MAX;
		LtHit = result;

	}
	LightHit DirectionalLight::getLightHit(const Point & p) const
	{
		return LtHit;
	}
	RGBColor DirectionalLight::getIntensity(const LightHit & irr) const
	{
		return color;
	}
}