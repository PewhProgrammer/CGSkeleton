#ifndef CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER
#define CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>

#include <rt\intersection.h>
#include <core\matrix.h>

namespace rt {

class Intersection;
class SphericalCoordMapper : public CoordMapper {
private:
	Point origin;
	Vector zen, x_axis, y_axis;

	Matrix projectionMatrix;
	Matrix kai; 
	float radial_distx, radial_disty;
public:
    SphericalCoordMapper();
    SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef);
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif
