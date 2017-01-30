#include "aabox.h"

using namespace rt;
rt::AABox::AABox(const Point & corner1, const Point & corner2, CoordMapper * texMapper, Material * material)
{
	this->min = corner1; this->max = corner2; 

	PlaneX1 = InfinitePlane(min, Vector(1.0f, 0.0f, 0.0f), nullptr, nullptr);
	PlaneX2 = InfinitePlane(max, Vector(1.0f, 0.0f, 0.0f), nullptr, nullptr);

	PlaneY1 = InfinitePlane(min, Vector(0.0f, 1.0f, 0.0f), nullptr, nullptr);
	PlaneY2 = InfinitePlane(max, Vector(0.0f, 1.0f, 0.0f), nullptr, nullptr);

	PlaneZ1 = InfinitePlane(min, Vector(0.0f, 0.0f, 1.0f), nullptr, nullptr);
	PlaneZ2 = InfinitePlane(max, Vector(0.0f, 0.0f, 1.0f), nullptr, nullptr);

	area = 2 * (corner2.x - corner1.x) + 2 * (corner2.y - corner1.y) + 2 * (corner2.z - corner1.z);
}
BBox AABox::getBounds() const
	{
		return BBox(min, max);
	}
	Intersection AABox::intersect(const Ray & ray, float previousBestDistance) const
	{
		/* slabs technique*/

		//span 6 planes


		std::map<float, Intersection> IntersectionMap;

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
		float farMin = rt::min(TfarX, TfarY, TfarZ);

		std::map<float, Intersection>::iterator i = IntersectionMap.find(nearMax);

		if (farMin <= nearMax || i->first > previousBestDistance)
			return Intersection::failure();

		return Intersection(i->first, ray, this, i->second.normal(), i->second.local());
	}
	Point AABox::sample() const
	{
		NOT_IMPLEMENTED;
	}
	float AABox::getArea() const
	{
		return area;
	}