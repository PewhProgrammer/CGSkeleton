#include "flatmaterial.h"

namespace rt {
	FlatMaterial::FlatMaterial(Texture * texture)
	{
		tex = texture;
	}
	RGBColor FlatMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		return RGBColor().rep(.0f);
	}
	RGBColor FlatMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return tex->getColor(texPoint);
	}
	Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return SampleReflectance(Vector().rep(0.0f), RGBColor().rep(0.0f));
	}
}