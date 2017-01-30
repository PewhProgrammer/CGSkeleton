#ifndef CG1RAYTRACER_SOLIDS_SPECIAL_HEADER
#define CG1RAYTRACER_SOLIDS_SPECIAl_HEADER

#include <rt/solids/solid.h>
#include <core/float4.h>
#include <core\vector.h>

#include <rt\bbox.h>
#include <rt\intersection.h>

namespace rt {

	class Special : public Solid {
	public:
		Special() {}
		Special(CoordMapper* texMapper, Material* material);
		virtual BBox getBounds() const;
		virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
		virtual Point sample() const;
		virtual float getArea() const;
	};

}


#endif
