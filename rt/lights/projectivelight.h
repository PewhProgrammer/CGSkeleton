#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>

#include <main\a_julia.h>
#include <rt\solids\infiniteplane.h>

namespace rt {

	class ProjectiveLight : public Light {
	private:
		int resX, resY; 
		Point pos;
		Vector dir;
		float horizontalOpeningAngle, verticalOpeningAngle;

		Vector spanX, spanY;
	public:
		ProjectiveLight() {}
		ProjectiveLight(const Point & position, const Vector& direction, float verticalOpeningAngle, float horizonalOpeningAngle);
		virtual LightHit getLightHit(const Point& p) const;
		virtual RGBColor getIntensity(const LightHit& irr) const;
	};

}

#endif

