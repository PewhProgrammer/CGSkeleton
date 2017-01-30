#include "raytrace.h"

namespace rt {
	RGBColor RayTracingIntegrator::getRadiance(const Ray & ray) const
	{
		
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
		Vector toViewer = -ray.d ;

		for (Light* src : this->world->light) {

			//compute shadowRay
			LightHit LtHit = src->getLightHit(it.hitPoint());
			Ray shadowRay = Ray(itPoint + LtHit.direction * 0.0001f, LtHit.direction);
			Intersection shadowIT = world->scene->intersect(shadowRay, FLT_MAX);

			//confirm ray,shadowRay on same side
			float angleRay = dot(it.normal(),toViewer); // assuming toViewer is normalized
			float angleShadowRay = dot(it.normal(), LtHit.direction.normalize());

			if (((angleRay > 0) && (angleShadowRay > 0)) || (angleRay < 0 && angleShadowRay < 0)) { //have to have same pre-sign
				if (!shadowIT || (shadowIT.distance > LtHit.distance)) { // either no intersection or intersection out of bounds
					
					L_i = L_i + 
						src->getIntensity(LtHit) * 
						it.solid->material->getReflectance(getCoords, it.normal(),toViewer,-LtHit.direction );

				}
			}
		}

		L_i = L_i + it.solid->material->getEmission(getCoords, it.normal(), toViewer);
		
		if (L_i.r == 0)
			float k = 2; 
		return L_i;
	}
}