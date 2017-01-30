#include "combine.h"

namespace rt {
	CombineMaterial::CombineMaterial()
	{
	}
	void CombineMaterial::add(Material * material, float weight)
	{
		material_weight pair(material,weight);
		mats.push_back(pair);
	}
	RGBColor CombineMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		RGBColor result(0.0f, 0.0f, 0.0f);

		for (material_weight m_w : mats) {
			result = result + m_w.first->getReflectance(texPoint,normal,outDir,inDir) * m_w.second;
		}

		return result;
	}
	RGBColor CombineMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		RGBColor result(0.0f, 0.0f, 0.0f);

		for (material_weight m_w : mats){
			result = result + m_w.first->getEmission(texPoint,normal,outDir) * m_w.second;
		}

		return result;
	}
	Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		Material::SampleReflectance sR(Vector(0,0,0),RGBColor(0,0,0)); 

		for (material_weight m_w : mats) {
			sR.direction = sR.direction + m_w.first->getSampleReflectance(texPoint, normal, outDir).direction;
			sR.reflectance = sR.reflectance + m_w.first->getSampleReflectance(texPoint, normal, outDir).reflectance * m_w.second;
		}

		sR.direction = sR.direction.normalize();
		return sR;
	}
	Material::Sampling CombineMaterial::useSampling() const
	{
		bool all_flag = false;
		bool sec_flag = false;
		bool not_flag = false;

		for(material_weight m_w : mats) {
			switch (m_w.first->useSampling()) {
			case Material::SAMPLING_ALL: {
				all_flag = true;
				break;
			}
			case Material::SAMPLING_SECONDARY: {
				sec_flag = true;
				break;
			}
			case Material::SAMPLING_NOT_NEEDED: {
				not_flag = true;
				break;
			}
			}
		}

		if (sec_flag || (all_flag && not_flag)) return SAMPLING_SECONDARY;
		if (all_flag) return SAMPLING_ALL;
		
		return SAMPLING_NOT_NEEDED;
	}
}