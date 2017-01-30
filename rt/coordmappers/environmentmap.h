#ifndef CG1RAYTRACER_COORDMAPPERS_ENVIRONMENTMAP_HEADER
#define CG1RAYTRACER_COORDMAPPERS_ENVIRONMENTMAP_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>

#include <rt\intersection.h>
#include <core\matrix.h>

namespace rt {

	class Intersection;
	class EnvironmentCoordMapper : public CoordMapper {
	public:
		EnvironmentCoordMapper();
		virtual Point getCoords(const Intersection& hit) const;
	};

}

#endif
