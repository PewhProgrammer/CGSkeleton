#ifndef CG1RAYTRACER_LIGHTS_AMBIENT_HEADER
#define CG1RAYTRACER_LIGHTS_AMBIENT_HEADER

#include <rt/lights/light.h>

#include <core\color.h>


namespace rt {

	class AmbientLight : public Light {
	private:
		RGBColor intensity;
	public:
		AmbientLight() {}
		AmbientLight(RGBColor &power);
		virtual LightHit getLightHit(const Point& p) const;
		virtual RGBColor getIntensity(const LightHit& irr) const;
	};

}

#endif

