#include "quad.h"
#include "disc.h"

namespace rt {
	BBox Disc::getBounds() const
	{
		NOT_IMPLEMENTED;
	}
	Intersection Disc::intersect(const Ray & ray, float previousBestDistance) const
	{
		InfinitePlane plane = InfinitePlane(center, norm, this->texMapper, this->material);
		Intersection it = plane.intersect(ray, previousBestDistance);

		if (!it) return Intersection::failure();

		Point p = ray.o + ray.d * it.distance;
		float dist = (p - center).length();
		if (dist > radius) return Intersection::failure();

		return Intersection(it.distance, ray, this, norm, Point());
	}
	Point Disc::sample() const
	{
		NOT_IMPLEMENTED;
	}
	float Disc::getArea() const
	{
		return area;
	}
}