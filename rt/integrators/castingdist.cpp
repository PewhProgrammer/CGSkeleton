#include "castingdist.h"

#define op(a,b,c,d,e) (((a - b) * c) / d) + e

namespace rt {
	RGBColor RayCastingDistIntegrator::getRadiance(const Ray & ray) const
	{
		//http://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
		// NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin

		Intersection it = this->world->scene->intersect(ray, FLT_MAX);
		if (it) {
			Vector normal;
			float c = (dot(ray.d, it.normal()));

			if (c < 0) {
				normal = -it.normal();
				c = (dot(ray.d, normal));
			}

			float currentDistance = it.distance;
			if (nearDist > currentDistance)
				return nearColor * c;
			else if (farDist < currentDistance)
				return farColor * c;

			float r, g, b; 

			float oldRange = farDist - nearDist;

			float newRange = farColor.r - nearColor.r;
			r = op(currentDistance, nearDist, newRange, oldRange, nearColor.r);

			newRange = farColor.g - nearColor.g;
			g = op(currentDistance, nearDist, newRange, oldRange, nearColor.g);

			newRange = farColor.b - nearColor.b;
			b = op(currentDistance, nearDist, newRange, oldRange, nearColor.b);

			return RGBColor(r, g, b) *c;
		}

		return RGBColor::rep(0);
	}
}