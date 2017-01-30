#include "bmap.h"

namespace rt {
	BumpMapper::BumpMapper(Triangle * base, Texture * bumpmap, const Point & bv1, const Point & bv2, const Point & bv3, float vscale)
	{
		this->base = base;
		bump = bumpmap;
		v1 = bv1;
		v2 = bv2;
		v3 = bv3;

		this->vscale = vscale;
	}
	BBox BumpMapper::getBounds() const
	{
		return base->getBounds();
	}

	/*theory
	if gradient is extrem, normal will alter accordingly*/
	Intersection BumpMapper::intersect(const Ray & ray, float previousBestDistance) const
	{
		Intersection it = this->base->intersect(ray, previousBestDistance);
		if (!it) return Intersection::failure();

		Point local = it.local();

		//Point texCoord = lerpbar(v1, v2, v3, local.x, local.y); //local -> u,v,w
		local = lerpbar(v3, v2, v1, local.x, local.y);

		float dx = (bump->getColorDX(local)).g; //r,g,b doesnt matter cuse we work with gray values
		float dy = (bump->getColorDY(local)).g; //compute gradient

		//dx = dx*vscale; dy = dy*vscale;

		/*Vector xy31 = v3 - v1; //get spanning vectors ex ey
		Vector xy21 = v2 - v1;

		float cons, u, v;

		cons = (xy31.x * xy21.y - xy21.x * xy31.y);

		u = cons == 0 ? 0 : (dy*xy31.x - dx*xy31.y) / cons; //prevent div 0
		v = xy31.x == 0 ? 0 : (dx - u * xy21.x) / xy31.x;*/

		//Vector perpNormal = it.normal() + u * base->ac + v * base->ab;
		Vector perpNormal = it.normal() + dx * base->ac + dy * base->ab;
		//perpNormal = perpNormal *vscale; //i'd rather assume to scale vertices

		 return Intersection(
			 it.distance,
			 it.ray,
			 it.solid,
			 perpNormal.normalize(),
			 local);
	}
	void BumpMapper::setMaterial(Material * m)
	{
		base->setMaterial(m);
	}
	void BumpMapper::setCoordMapper(CoordMapper * cm)
	{
		base->setCoordMapper(cm);
	}
}