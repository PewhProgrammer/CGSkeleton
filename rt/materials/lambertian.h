#ifndef CG1RAYTRACER_MATERIALS_LAMBERTIAN_HEADER
#define CG1RAYTRACER_MATERIALS_LAMBERTIAN_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

class LambertianMaterial : public Material {
private:
	Texture* emission;
	Texture* diffuse;
	float invPi = 1 / pi; 
public:
    LambertianMaterial(Texture* emission, Texture* diffuse);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
};

}

#endif
