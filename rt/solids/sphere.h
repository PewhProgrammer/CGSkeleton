#ifndef CG1RAYTRACER_SOLIDS_SPHERE_HEADER
#define CG1RAYTRACER_SOLIDS_SPHERE_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>

#include <rt\intersection.h>
#include <rt\bbox.h>

namespace rt {

class Sphere : public Solid {
private:
	Point center;
	float radius,area; 
	Point boxmin, boxmax;
public:
    Sphere() {}
	Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material) :
		center(center), radius(radius) {
		this->material = material; 
		this->texMapper = texMapper; 
		area = 4 * pi*sqr(radius);

		boxmin = Point(center.x - radius, center.y - radius, center.z - radius);
		boxmax = Point(center.x + radius, center.y + radius, center.z + radius);
	}

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
    virtual float getArea() const;
};

}


#endif
