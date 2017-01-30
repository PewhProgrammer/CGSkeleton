#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>
#include <core\color.h>

#include <rt\world.h>
#include <rt\intersection.h>
#include <rt\lights\light.h>
#include <rt\solids\solid.h>
#include <rt\materials\material.h>

#include <rt\coordmappers\world.h>

namespace rt {

class World;
class Ray;
class RGBColor;

class RecursiveRayTracingIntegrator : public Integrator {
private:
	bool* iter_flag = false;
public:
    RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
};

}

#endif
