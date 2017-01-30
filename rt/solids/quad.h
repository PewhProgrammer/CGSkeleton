#ifndef CG1RAYTRACER_SOLIDS_QUAD_HEADER
#define CG1RAYTRACER_SOLIDS_QUAD_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>

#include <rt\intersection.h>
#include <rt\bbox.h>
#include <rt\solids\triangle.h>

#include <core\random.h>

namespace rt {

class Quad : public Solid {
private:
	Point p1;
	Point p2;
	Vector span1, span2;
	float area;
public:
    Quad() {}
	Quad(const Point& v1, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
		:p1(v1), span1(span1), span2(span2),p2(v1+span1+span2) {
		this->texMapper = texMapper; 
		this->material = material;
		area = cross(span1, span2).length();
	}

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
    virtual float getArea() const;
};

}

#endif
