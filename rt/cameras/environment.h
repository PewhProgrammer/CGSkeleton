#ifndef CG1RAYTRACER_CAMERAS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_CAMERAS_ENVIRONMENT_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>

#include <rt\ray.h>

namespace rt {

	class EnvironmentCamera : public Camera {

	private:
		Point center;
		Vector up; 
		Vector forward;
		Vector spanX; 
		float radiusX, radiusY;


	public:
		EnvironmentCamera(
			const Point& center,
			const Vector& forward,
			const Vector& up,
			float radiusX,
			float radiusY
		);

		virtual Ray getPrimaryRay(float x, float y) const;
	};

}


#endif