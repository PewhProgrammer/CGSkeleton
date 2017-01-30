#include "intersection.h"

namespace rt {
	Intersection Intersection::failure()
	{
		return Intersection(-1);
	}
	Intersection::Intersection(float distance, const Ray & ray, const Solid * solid, const Vector & normal, const Point & uv)
	{
		this->distance = distance; 
		this->ray = ray; 
		this->solid = solid; 
	
		this->norm = normal.normalize(); 
		this->uv = uv; 
	}
	Point Intersection::hitPoint() const
	{
		return this->ray.o + this->ray.d * distance; 
	}
	Vector Intersection::normal() const
	{
		return this->norm; 
	}
	Point Intersection::local() const
	{
		return uv;
	}
	Intersection::operator bool()
	{
		return distance > 0; //will treat special as true case
	}
}