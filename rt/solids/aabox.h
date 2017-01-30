#ifndef CG1RAYTRACER_SOLIDS_BOX_HEADER
#define CG1RAYTRACER_SOLIDS_BOX_HEADER

#include <rt/solids/solid.h>
#include <rt/bbox.h>

#include <rt\intersection.h>
#include <rt\solids\infiniteplane.h>
#include <map>

namespace rt {

class AABox : public Solid {
private:
	Point min, max; 
	float area; 
	InfinitePlane PlaneX1,PlaneX2,PlaneY1,PlaneY2,PlaneZ1,PlaneZ2;
public:
    AABox() {}
	AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual Point sample() const;
    virtual float getArea() const;
};

}

#endif
