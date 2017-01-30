#include "lambertian.h"

namespace rt {
	LambertianMaterial::LambertianMaterial(Texture * emission, Texture * diffuse)
	{
		this->emission = emission;
		this->diffuse = diffuse;
	
	}
	RGBColor LambertianMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		//make sure that both vectors are normalized
		float cos_angle = dot(normal, inDir);

		//absolute value of cos_angle 
		//invPi to maintain energy conservation across upper hemisphere
		return RGBColor().rep(abs(cos_angle)) * diffuse->getColor(texPoint)  *invPi;
	}
	RGBColor LambertianMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return emission->getColor(texPoint);
	}
	Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return SampleReflectance(Vector().rep(0.0f), RGBColor().rep(0.0f));
	}
	Material::Sampling LambertianMaterial::useSampling() const
	{
		return SAMPLING_NOT_NEEDED;
	}
}