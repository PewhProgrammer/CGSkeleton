#include "phong.h"

namespace rt {
	PhongMaterial::PhongMaterial(Texture * specular, float exponent)
	{
		this->specular = specular;
		exp = exponent;

		normalization_fac = (exponent + 2) / (2 * pi); // s.t. f is energy conserving
	}
	/*
	Implementation out of lecture slides
	*/
	RGBColor PhongMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		//purely specular material defined by
		//- color weight 
		//- reflection exp

		Vector reflectedVector_normalized = (2 * (dot(inDir, normal)*normal) - inDir).normalize(); 
		float highlight_exp = pow(abs(dot(reflectedVector_normalized, outDir)),exp);

		float cos_angle = abs(dot(normal,inDir));


		return specular->getColor(texPoint) * highlight_exp * normalization_fac * cos_angle;
	}
	RGBColor PhongMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		//doesnt emit, only reflect
		return RGBColor().rep(0.0f);
	}
	Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return SampleReflectance(Vector().rep(0.0f), RGBColor().rep(0.0f));
	}
	Material::Sampling PhongMaterial::useSampling() const
	{
		return Sampling::SAMPLING_NOT_NEEDED;
	}
}