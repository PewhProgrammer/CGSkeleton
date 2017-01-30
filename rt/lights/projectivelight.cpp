#include "projectivelight.h"

namespace rt {
	ProjectiveLight::ProjectiveLight(const Point & position, const Vector& direction, float verticalOpeningAngle, float horizonalOpeningAngle)
	{
		//construct image plane and project julia onto it
		pos = position;
		dir = (-direction).normalize();

		this->verticalOpeningAngle = verticalOpeningAngle;
		this->horizontalOpeningAngle = horizonalOpeningAngle;

		spanX = cross(dir, Vector(0,1,0)).normalize() * tan(horizonalOpeningAngle * 0.5f);
		spanY = cross(dir, spanX).normalize() * tan(verticalOpeningAngle * 0.5f);

		//spanX = spanX.normalize();
		//spanY = spanY.normalize();

		resX = 400;
		resY = 400;

	}
	LightHit ProjectiveLight::getLightHit(const Point & p) const
	{
		LightHit result;
		Vector q = pos - p;
		result.direction = q.normalize();
		result.distance = q.length();
		return result;

	}
	RGBColor ProjectiveLight::getIntensity(const LightHit & irr) const{
		
		//take point light, do it over environment map
		//and change it to polar -> didnt work out

		Point plane_hit(this->pos + irr.direction * irr.distance);

		//span a plane around hitpoint and compute plane origins
		InfinitePlane plane = InfinitePlane(plane_hit, -irr.direction,nullptr,nullptr);
		Intersection it = plane.intersect(Ray(pos, dir), FLT_MAX);

		if (!it)
			return RGBColor(0, 0, 0);

		Point plane_origin = it.hitPoint();

		//check of prerequisite is fulfiled
		float e_1 = dot(dir, spanX);
		float e_2 = dot(dir, spanY);
		float e_3 = dot(spanX, spanY);

		assert(e_1 == 0 && e_2 == 0 && e_3 == 0);

		//compute x,y in respect to spanX,spanY 
		float x = dot(spanX, plane_hit - plane_origin);
		float y = dot(spanY, plane_hit - plane_origin);

		//we have x and y in screen space

		//it would go out of range
		if (abs(x) > 1 || abs(y) > 1) return RGBColor().rep(0.0f);

		//http://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
		// NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin

		x = (((x + 1) * (resX - 0)) / (1 + 1)) + 0;
		y = (((y + 1) * (resY - 0)) / (1 + 1)) + 0;

		//transform into image space
		//x = ((x + 1.0)  *0.5f) * resX - 0.5;
		//y = ((y + 1.0)  *0.5f) * resY - 0.5;

		//return RGBColor(1, 1, 1);
		return (a1computeColor(x, y, resX, resY));

	}
}