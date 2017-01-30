#ifndef CG1RAYTRACER_SOLIDS_INFINITEPLANE_HEADER
#define CG1RAYTRACER_SOLIDS_INFINITEPLANE_HEADER

#include <rt/solids/solid.h>
#include <core/float4.h>
#include <core\vector.h>

#include <rt\bbox.h>
#include <rt\intersection.h>

namespace rt {

class InfinitePlane : public Solid {
private:
	Point origin;
	Vector normal;
public:
    InfinitePlane() {}
    InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material):
		origin(origin),normal(normal)
	{
		this->material = material;
		this->texMapper = texMapper; 
	}

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
    virtual float getArea() const;
};

}


#endif
