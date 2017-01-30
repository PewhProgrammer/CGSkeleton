#include "triangle.h"

namespace rt {

	Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) {

		A = v1;
		B = v2;
		C = v3;
		ab = B - A;
		bc = C - B;
		ac = C - A;

		this->texMapper = texMapper;
		this->material = material;
		this->TriArea = cross(ab, ac).length() * 0.5f;
		this->invTriArea = 1 / TriArea;

		boxmin = min(min(v1, v2), v3);
		boxmax = max(max(v1, v2), v3);

	}

	BBox Triangle::getBounds() const
	{
		return BBox(boxmin, boxmax);
	}
	Intersection Triangle::intersect(const Ray & ray, float previousBestDistance) const
	{

		InfinitePlane plane = InfinitePlane(A, cross(ab, ac),this->texMapper,this->material);
		Intersection hit = plane.intersect(ray, previousBestDistance);
		if (!hit | hit.distance > previousBestDistance) return Intersection::failure();

		Point P = hit.hitPoint();

		float ABP_area = cross(ab, P - A).length() * 0.5f; 
		float ACP_area = cross(ac, P - A).length() * 0.5f;
		float BCP_area = cross(bc, P - B).length() * 0.5f; 

		float u, v, w;

		u = ABP_area * invTriArea;
		v = ACP_area * invTriArea;
		w = BCP_area * invTriArea;
		
		double sum = u + v + w; 

		if (sum > 1.0001)
			return Intersection::failure();

		return Intersection(hit.distance, ray, this, hit.normal(), Point(u, v, w));
	}
	Point Triangle::sample() const
	{
		/* returns arbitriary point on the triangle*/

		float rand1 = random();
		float rand2 = random();

		if ((rand1 + rand2)  < 1) {
			return (lerpbar(A, B, C, rand1, rand2));
		}
		else {
			return (lerpbar(A, B, C, 1 - rand1, 1 - rand2));
		}
	}
	float Triangle::getArea() const
	{
		return this->TriArea;
	}
}