#ifndef CG1RAYTRACER_LIGHTS_AREALIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_AREALIGHT_HEADER

#include <core/vector.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>

#include <core\color.h>
#include <rt\materials\material.h>


namespace rt {

class AreaLight : public Light {
private:
	Solid* src;
public:
	AreaLight() {}
	AreaLight(Solid* source);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif

