#ifndef CG1RAYTRACER_FISHEYE_HEADER
#define CG1RAYTRACER_FISHEYE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <math.h>

#include <rt\ray.h>

namespace rt {

	class FisheyeCamera : public Camera {

	private:
		Point center;
		Vector forward, up;
		Vector dir;
		Vector spanX, spanY;
		float aperture; 

	public:
		FisheyeCamera(
			const Point& center,
			const Vector& forward,
			const Vector& up,
			float aperture
		);

		virtual Ray getPrimaryRay(float x, float y) const;
	};

}

#endif