#ifndef CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>

#include <rt\ray.h>
#include <core\random.h>

namespace rt {

class DOFPerspectiveCamera : public Camera {
private:
	Point center;
	Vector forward, spanX, spanY,right,up;
	float verticalOpeningAngle, horizontalOpeningAngle, focalDistance, radius;
public:
    DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
        );

    virtual Ray getPrimaryRay(float x, float y) const;

};

}


#endif
