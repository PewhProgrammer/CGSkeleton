#include "simplegroup.h"

namespace rt {

	BBox SimpleGroup::getBounds() const
	{
		NOT_IMPLEMENTED; 
	}
	Intersection SimpleGroup::intersect(const Ray & ray, float previousBestDistance) const
	{

		Intersection result = Intersection::failure(); 

		float bestDist = previousBestDistance; 
		for (Primitive* prim : container) {
			Intersection hit = prim->intersect(ray, bestDist);
			if (hit) {
				result = hit; 
				bestDist = hit.distance; 
			}
		}

		return result; 
	}
	void SimpleGroup::rebuildIndex()
	{
		this->built_flag = true; 
	}
	void SimpleGroup::add(Primitive * p)
	{
		this->container.push_back(p);
	}
	void SimpleGroup::setMaterial(Material * m)
	{
		NOT_IMPLEMENTED;
	}
	void SimpleGroup::setCoordMapper(CoordMapper * cm)
	{
		NOT_IMPLEMENTED;
	}
}