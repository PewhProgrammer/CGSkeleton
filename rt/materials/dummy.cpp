#include "dummy.h"

namespace rt {
	DummyMaterial::DummyMaterial()
	{
		//TODO: Implementation
	}
	RGBColor DummyMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		float cos_i =dot(inDir.normalize(), normal); // normal, normalisiert?
			
		if (cos_i < 0)
			cos_i = 0 - cos_i;

 		return RGBColor::rep(fr*cos_i);
	}
	RGBColor DummyMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor::rep(0);
	}
	Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		NOT_IMPLEMENTED;
	}
}