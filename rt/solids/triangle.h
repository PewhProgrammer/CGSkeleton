#ifndef CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER
#define CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>

#include <rt\intersection.h>
#include <rt\bbox.h>
#include <rt\solids\infiniteplane.h>

#include <core\random.h>
#include <core\interpolate.h>

namespace rt {

class Triangle : public Solid {
private:
	Point A, B, C; 
	float invTriArea;
	float TriArea;
	Point boxmin, boxmax;
public:
	Vector ab, ac, bc;
    Triangle() {}
	Triangle(Point vertices[3], CoordMapper* texMapper, Material* material) {
		Triangle(vertices[0],vertices[1],vertices[2],texMapper,material);
	}
	Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
    virtual float getArea() const;
};

}

#endif
