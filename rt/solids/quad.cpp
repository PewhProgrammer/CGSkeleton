#include "quad.h"

namespace rt {
	BBox Quad::getBounds() const
	{
		return BBox(min(p1, p2), max(p1, p2));
	}
	Intersection Quad::intersect(const Ray & ray, float previousBestDistance) const
	{

		Triangle tri1 = Triangle(p1, p1 + span1, p1 + span2, this->texMapper, this->material);
		Intersection result = tri1.intersect(ray, previousBestDistance);
		if (result) return Intersection(result.distance, ray, this, result.normal(), Point());
		
		Triangle tri2 = Triangle(p2, p1 + span1, p1 + span2, this->texMapper, this->material);
		result = tri2.intersect(ray, previousBestDistance);
		if (result) return Intersection(result.distance, ray, this, result.normal(), Point());

		return Intersection::failure();
	}
	Point Quad::sample() const
	{
		/* returns point in the span*/
		return p1 + span1 * random() + span2 *random();

		/*Point v2 = p1 + span1;
		Point v3 = p1 + span1 + span2;
		Point v4 = p1 + span2;
		float r1 = random(0.0, float((v3 - v2).length()));
		float r2 = random(0.0, float((v2 - p1).length()));
		Point x = v2 + r1*(v3 - v2).normalize();
		Point y = x + r2*(p1 - v2).normalize();
		return y;*/
	}
	float Quad::getArea() const
	{
		return area;
	}
}