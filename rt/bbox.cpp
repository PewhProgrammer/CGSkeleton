#include "bbox.h"

typedef std::pair<float, float> f2;

namespace rt {
	BBox BBox::empty()
	{
		return BBox(Point().rep(FLT_MAX), Point().rep(-FLT_MAX));
	}
	BBox BBox::full()
	{
		return BBox(Point().rep(-FLT_MAX), Point().rep(FLT_MAX)) ;
	}
	void BBox::extend(const Point & point)
	{
		min = rt::min(point, min);
		max = rt::max(point, max);

	}
	void BBox::extend(const BBox & bbox)
	{
		max = rt::max(bbox.max, max);
		min = rt::min(bbox.min, min);

	}
	std::pair<float, float> BBox::intersect(const Ray & ray) const
	{
	
		//if unbound return intersection immediately?

		float invRayDir, near, far;
		float t_0 = -FLT_MAX; // needs to be overwritten later 
		float t_1 = FLT_MAX;
		for (int i = 0; i < 3; i++) {
			invRayDir = 1.f / ray.d[i]; // more efficient
			near = (min[i] - ray.o[i]) * invRayDir;
			far = (max[i] - ray.o[i]) * invRayDir;
			if (near > far) std::swap(near, far); // assign near and far

			//biggest near and smallest far for slabs
			t_0 = near > t_0 ? near : t_0;
			t_1 = far < t_1 ? far : t_1; 
		}

		//if biggest near is smaller than smallest t1, we have intersection
		//if not then t0 > t1 and we throw failure
		return f2(t_0, t_1);

		
		// ------ ALTERNATIVE WITH PLANES ------ MUCH SLOWER 
		/*std::map<float, Intersection> IntersectionMap;

		InfinitePlane PlaneX1 = InfinitePlane(min, Vector(1.0f, 0.0f, 0.0f), nullptr, nullptr);
		InfinitePlane PlaneX2 = InfinitePlane(max, Vector(1.0f, 0.0f, 0.0f), nullptr, nullptr);

		InfinitePlane PlaneY1 = InfinitePlane(min, Vector(0.0f, 1.0f, 0.0f), nullptr, nullptr);
		InfinitePlane PlaneY2 = InfinitePlane(max, Vector(0.0f, 1.0f, 0.0f), nullptr, nullptr);

		InfinitePlane PlaneZ1 = InfinitePlane(min, Vector(0.0f, 0.0f, 1.0f), nullptr, nullptr);
		InfinitePlane PlaneZ2 = InfinitePlane(max, Vector(0.0f, 0.0f, 1.0f), nullptr, nullptr);

		Intersection PlaneX1Inter = PlaneX1.intersect(ray, FLT_MAX);
		Intersection PlaneX2Inter = PlaneX2.intersect(ray, FLT_MAX);

		Intersection PlaneY1Inter = PlaneY1.intersect(ray, FLT_MAX);
		Intersection PlaneY2Inter = PlaneY2.intersect(ray, FLT_MAX);

		Intersection PlaneZ1Inter = PlaneZ1.intersect(ray, FLT_MAX);
		Intersection PlaneZ2Inter = PlaneZ2.intersect(ray, FLT_MAX);

		IntersectionMap[PlaneX1Inter.distance] = PlaneX1Inter;
		IntersectionMap[PlaneX2Inter.distance] = PlaneX2Inter;

		IntersectionMap[PlaneY1Inter.distance] = PlaneY1Inter;
		IntersectionMap[PlaneY2Inter.distance] = PlaneY2Inter;

		IntersectionMap[PlaneZ1Inter.distance] = PlaneZ1Inter;
		IntersectionMap[PlaneZ2Inter.distance] = PlaneZ2Inter;

		float TnearX = 0.0;  float TfarX = 0.0;
		float TnearY = 0.0;  float TfarY = 0.0;
		float TnearZ = 0.0;  float TfarZ = 0.0;

		if (PlaneX1Inter.distance <= PlaneX2Inter.distance) { TnearX = PlaneX1Inter.distance; TfarX = PlaneX2Inter.distance; }
		else { TnearX = PlaneX2Inter.distance;	TfarX = PlaneX1Inter.distance; }

		if (PlaneY1Inter.distance <= PlaneY2Inter.distance) { TnearY = PlaneY1Inter.distance; TfarY = PlaneY2Inter.distance; }
		else { TnearY = PlaneY2Inter.distance;	TfarY = PlaneY1Inter.distance; }

		if (PlaneZ1Inter.distance <= PlaneZ2Inter.distance) { TnearZ = PlaneZ1Inter.distance; TfarZ = PlaneZ2Inter.distance; }
		else { TnearZ = PlaneZ2Inter.distance;	TfarZ = PlaneZ1Inter.distance; }

		float nearMax = rt::max(TnearX, TnearY, TnearZ);
		float endpointDist;
		if (TnearX > TnearY) {
			if (TnearX > TnearZ) {
				nearMax = TnearX; 
				endpointDist = TfarX; 
			}
			else {
				nearMax = TnearZ; 
				endpointDist = TnearZ;
			}
		}
		else {
			if (TnearY > TnearZ) {
				nearMax = TnearY;
				endpointDist = TfarY;
			}
			else {
				nearMax = TnearZ;
				endpointDist = TnearZ;
			}
		}
		float farMin = rt::min(TfarX, TfarY, TfarZ);

		std::map<float, Intersection>::iterator i = IntersectionMap.find(nearMax);

		if (farMin <= nearMax) {
			// t_1 > t_2 means no intersection
			return std::pair<float,float>(i->first,farMin);
		}

		std::map<float, Intersection>::iterator j = IntersectionMap.find(endpointDist);

		return std::pair<float, float>(i->first, endpointDist); */
	}
	bool BBox::isUnbound()
	{
		return
			(min.x == -FLT_MAX) |
			( min.y == -FLT_MAX) |
			( min.z == -FLT_MAX) |
			(max.x == FLT_MAX ) |
			(max.y == FLT_MAX) |
			(max.z == FLT_MAX);
	}
}