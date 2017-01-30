#include "casting.h"

namespace rt {
	RGBColor RayCastingIntegrator::getRadiance(const Ray & ray) const
	{
		Intersection it = this->world->scene->intersect(ray, FLT_MAX);
		if (it) {
			Vector normal;
			float c = (dot(ray.d, it.normal()));

			if (c < 0) {
				normal = -it.normal(); 
				c = (dot(ray.d, normal));
			}

			return RGBColor::rep(c).clamp();
		}

		return RGBColor::rep(0);
	}
}