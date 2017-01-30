#include "spotlight.h"

namespace rt {
	SpotLight::SpotLight(const Point & position, const Vector & direction, float angle, float exp, const RGBColor & intensity)
	{
		pos = position;
		dir = (-direction).normalize();
		this->angle = angle;
		this->exp = exp;
		Intensity = intensity; 

	}
	LightHit SpotLight::getLightHit(const Point & p) const
	{
		
		LightHit result; 
		Vector q = pos - p;
		result.direction = q.normalize();
		result.distance = q.length();

		return result;
	}
	RGBColor SpotLight::getIntensity(const LightHit & irr) const
	{
		//c++ acos works with radians
		//dot gives angle between irr and dir of light source

		//angle is given in radians 
		float rad = acos(dot(irr.direction, dir));

		//rad = rad > 0 ? rad : 2*pi - rad;

		if (rad > angle)
			return RGBColor(0, 0, 0);

		return (Intensity * pow(cos(rad), exp)) / sqr(irr.distance);
	}
}