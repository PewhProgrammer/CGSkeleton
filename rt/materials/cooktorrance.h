#ifndef CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER
#define CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

	class CookTorrance : public Material {
	private:
		Texture* diffuse;
		Texture* specular;

		float invPi = 1 / pi;
		float normalization_fac,eta, kappa,m;

	public:
		CookTorrance(float eta, float kappa,float m, Texture * diffuse,Texture* specular);
		virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
		virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
		virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
		virtual Sampling useSampling() const;
	};

}

#endif