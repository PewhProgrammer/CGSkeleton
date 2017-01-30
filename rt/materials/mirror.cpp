#include "mirror.h"

namespace rt {
	MirrorMaterial::MirrorMaterial(float eta, float kappa)
	{
		this->eta = eta;
		this->kappa = kappa;
	}
	RGBColor MirrorMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		return RGBColor().rep(0.0f);
	}
	RGBColor MirrorMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor().rep(0.0f);
	}

	/*
	Taken from lecture slides
	*/
	Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		Vector invOutDir = -outDir;

		//dot should be absolute value
		Vector inDir = (2 * dot(invOutDir, normal)*normal - invOutDir).normalize() ;

		//computation of incident ray and normal
		float cos_angle = abs(dot(normal, invOutDir));
		//float cos_angle = dot(normal, outDir);

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

		return SampleReflectance(-inDir, RGBColor::rep(fresnel));

	}
	Material::Sampling MirrorMaterial::useSampling() const
	{
		return Sampling::SAMPLING_ALL;
	}
}