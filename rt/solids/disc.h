#ifndef CG1RAYTRACER_SOLIDS_DISC_HEADER
#define CG1RAYTRACER_SOLIDS_DISC_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>

#include <rt\intersection.h>
#include <rt\bbox.h>
#include <rt\solids\infiniteplane.h>

namespace rt {

class Disc : public Solid {
private:
	Point center;
	Vector norm;
	float radius,area; 
public:
    Disc() {}
	Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
		: center(center), norm(normal), radius(radius) {
		this->texMapper = texMapper;
		this->material = material;
		area = 2 * pi*radius; 
	}

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual Point sample() const;
    virtual float getArea() const;
};

}


#endif
