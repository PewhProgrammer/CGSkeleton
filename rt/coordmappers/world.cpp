#include "world.h"

namespace rt {
	WorldMapper::WorldMapper()
	{
		this->scale = Float4().rep(1);
	}
	WorldMapper::WorldMapper(const Float4 & scale)
	{
		this->scale = scale;
	}
	Point WorldMapper::getCoords(const Intersection & hit) const
	{
		Float4 hitPoint(hit.hitPoint());

		return Point(scale*hitPoint);
	}
}