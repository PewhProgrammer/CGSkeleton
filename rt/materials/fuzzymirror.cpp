#include "fuzzymirror.h"

namespace rt {
	FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
	{
		this->eta = eta; this->kappa = kappa; this->fuzzyangle = fuzzyangle; 
	}
	RGBColor FuzzyMirrorMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		return RGBColor().rep(0.0f);
	}
	RGBColor FuzzyMirrorMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor().rep(0.0f);
	}
	Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		//may deviate at max by fuzzyangle
		/* http://mathworld.wolfram.com/DiskPointPicking.html */
		Vector invOutDir = -outDir;

		//dot should be absolute value
		float k = dot(invOutDir, normal); 
		float k1 = dot(outDir, normal);
		Vector inDir = (2 * dot(invOutDir, normal)*normal - invOutDir).normalize();
		//Vector inDir = (2 * dot(outDir, normal)*normal - outDir).normalize();

		//perputate inDir
		float radius = tan(fuzzyangle * 0.5f); // radius of imaginary disc, Opposite / Adjacent, adjacent = 1
		radius = random(0, radius);

		//invOutDir = Vector(1, 0, 0);
		Vector spanX = cross(inDir, Vector(0, 0, 1)) ;
		Vector spanY = cross(inDir, spanX);

		float theta = random(0, 2 * pi);
		float x = sqrt(radius) * cos(theta);
		float y = sqrt(radius) * sin(theta);

		/*
		float rad = radius * sqrt(random());
		float theta = 2 * pi * random();

		float x1 = rad * cos(theta);
		float y1 = rad * sin(theta);*/

		Vector perputatedR = inDir + spanX * x + spanY * y; 

		float cos_angle = abs(dot(normal, -perputatedR));

		//parallel light
		float r_par =
			((sqr(eta) + sqr(kappa))*sqr(cos_angle) - 2.0f * eta*cos_angle + 1.0f)
			/ ((sqr(eta) + sqr(kappa))*sqr(cos_angle) + 2.0f * eta*cos_angle + 1.0f);

		//perpendicular light
		float r_perp =
			((sqr(eta) + sqr(kappa)) - 2.0f * eta*cos_angle + sqr(cos_angle))
			/ ((sqr(eta) + sqr(kappa)) + 2.0f * eta*cos_angle + sqr(cos_angle));

		//unpolarized light
		float fresnel = (r_par + r_perp) * 0.5f;

		return SampleReflectance(-perputatedR, RGBColor::rep(fresnel));
	}
}