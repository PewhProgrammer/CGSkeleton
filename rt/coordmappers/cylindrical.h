#ifndef CG1RAYTRACER_COORDMAPPERS_CYLINDRICAL_HEADER
#define CG1RAYTRACER_COORDMAPPERS_CYLINDRICAL_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>

#include <rt\intersection.h>
namespace rt {

class Intersection;

class CylindricalCoordMapper : public CoordMapper {
private:
	Point origin;
	Vector longitudinalAxis ,x_axis, y_axis;
	float radial_distx, radial_disty;
public:
    CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis);
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif
