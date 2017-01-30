#include "recraytrace.h"

#define epsilon 0.0001f
uint16_t depth = 0;

namespace rt {
	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray & ray) const
	{
		if (depth > 6) {
			depth = 0; 
			return RGBColor().rep(0.0f);
		}

		Intersection it = world->scene->intersect(ray, FLT_MAX);
		if (!it)
			return RGBColor::rep(0.0f);

		//found intersection and compute lighting

		//create mapper; if in solid, we flood the stack
		WorldMapper wMapper(Float4::rep(1.0));

		Point getCoords = (it.solid->texMapper == nullptr) ? wMapper.getCoords(it) : it.solid->texMapper->getCoords(it);

		//precompute all values
		Point itPoint = it.hitPoint();
		RGBColor L_i(0, 0, 0);
		Vector toViewer = -ray.d;

		if (!it.solid->material) return RGBColor(0.2f,0.34f,0.66f);
		Material::Sampling sampling = it.solid->material->useSampling(); 

		if (sampling != Material::SAMPLING_NOT_NEEDED) {
			depth++;
			Material::SampleReflectance s =  it.solid->material->getSampleReflectance(it.local(),it.normal(),toViewer);
			Ray mirroredRay(itPoint + (s.direction*epsilon), s.direction);
			L_i =  L_i + getRadiance(mirroredRay) * s.reflectance;

			depth = 0; 
			//if all, we can stop here
			//else iterate over light src's
			if(sampling == Material::SAMPLING_ALL)
				return L_i; 
		}

		for (Light* src : this->world->light) {
			//compute shadowRay
			LightHit LtHit = src->getLightHit(it.hitPoint());
			if (LtHit.distance == 0) {
				L_i = L_i +
					src->getIntensity(LtHit)* //* RGBColor(139/255, 69/255, 19/255);
					it.solid->material->getReflectance(getCoords, it.normal(), toViewer, -it.normal());
				continue;
			}
			Ray shadowRay = Ray(itPoint + LtHit.direction * epsilon, LtHit.direction);
			Intersection shadowIT = world->scene->intersect(shadowRay, FLT_MAX);

			//confirm ray,shadowRay on same side
			float angleRay = dot(it.normal(), toViewer); // assuming toViewer is normalized
			float angleShadowRay = dot(it.normal(), LtHit.direction.normalize());

			if (((angleRay > 0) && (angleShadowRay > 0)) || (angleRay < 0 && angleShadowRay < 0) ) { //have to have same pre-sign
				if (!shadowIT || (shadowIT.distance > LtHit.distance)) { // either no intersection or intersection out of bounds

					L_i = L_i +
						src->getIntensity(LtHit) *
						it.solid->material->getReflectance(getCoords, it.normal(), toViewer, -LtHit.direction);

				}
			}
		}

		L_i = L_i + it.solid->material->getEmission(getCoords, it.normal(), toViewer);

		return L_i;
	}

}