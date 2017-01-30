#include "environmentmap.h"

namespace rt {
	EnvironmentCoordMapper::EnvironmentCoordMapper()
	{
	}
	Point EnvironmentCoordMapper::getCoords(const Intersection & hit) const
	{
		/* The reflection color used in the shading computation at a pixel is determined 
		by calculating the reflection vector at the point on the object and mapping it to the texel in the environment map 
		http://cgvr.cs.uni-bremen.de/teaching/cg_literatur/Spherical,%20Cubic,%20and%20Parabolic%20Environment%20Mappings.pdf page 15
		textures http://www.humus.name/index.php?page=Textures */

		//above implementation does not correlate with our exercise

		Ray ray = hit.ray;
		return Point(ray.d.x, ray.d.y, ray.d.z);
	}
}