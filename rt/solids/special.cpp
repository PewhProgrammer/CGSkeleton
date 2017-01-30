#include "special.h"

namespace rt {
	Special::Special(CoordMapper * texMapper, Material * material)
	{
		this->material = material;
		this->texMapper = texMapper;
	}
	BBox Special::getBounds() const
	{
		return BBox().full();
	}
	Intersection Special::intersect(const Ray & ray, float previousBestDistance) const
	{
		if (previousBestDistance < FLT_MAX) 
			return Intersection::failure();
		
		//return Intersection::failure();
		return Intersection(FLT_MAX,ray,this,Vector(0,0,1),Point(0,0,0));
	}
	Point Special::sample() const
	{
		return Point();
	}
	float Special::getArea() const
	{
		return FLT_MAX;
	}
}