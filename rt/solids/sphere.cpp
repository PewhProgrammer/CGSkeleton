#include "sphere.h"

namespace rt {
	BBox Sphere::getBounds() const
	{
		return BBox(boxmin, boxmax);
	}
	Intersection Sphere::intersect(const Ray & ray, float previousBestDistance) const
	{

		float b = dot(ray.d, (ray.o - center));

		float t_1, t_2;
		Point hit;
		Vector normal;

		float sol_ = sqr(b) - ((ray.o - center).length() * (ray.o - center).length())
			+ sqr(radius);

		if (sol_ < 0)
			return Intersection::failure();
	
		if (sol_ == 0) {
			t_1 = -b; 
			if(t_1 > previousBestDistance) return Intersection::failure();
			normal = (ray.o + t_1*ray.d ) - center;
			return Intersection(t_1, ray, this, normal.normalize(), ray.o + ray.d*t_1);
		}

		sol_ = sqrt(sol_);
		t_1 = -b + sol_;
		t_2 = -b  - sol_;

		t_1 = t_2 > 0 ? t_2 : t_1; 
		hit = ray.o + ray.d*t_1;
		normal = (hit - center).normalize();

		if (t_1 < previousBestDistance)
			return Intersection(t_1, ray, this, normal , hit);
		
		return Intersection::failure(); 

	}
	Point Sphere::sample() const
	{
		NOT_IMPLEMENTED;
	}
	float Sphere::getArea() const
	{
		return area;
	}
}