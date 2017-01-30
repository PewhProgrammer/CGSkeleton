#include "tmapper.h"

namespace rt {
	TriangleMapper::TriangleMapper(const Point & tv0, const Point & tv1, const Point & tv2)
	{
		//barycentric coordinates
		u = tv0; v = tv1; w = tv2;
	}
	TriangleMapper::TriangleMapper(Point ntv[3])
	{
		u = ntv[0]; v = ntv[1]; w = ntv[2];
	}
	Point TriangleMapper::getCoords(const Intersection & hit) const
	{
		//note: local should return cartesian, except for triangles

		Point bary_coord = hit.local();
		Point p1, p2, p3;

		/*
		w     u
		      v
		*/

		p1 = v * bary_coord.y;
		p2 = w * bary_coord.x;
		p3 = u * bary_coord.z;

		Point result = Point((p1.x + p3.x), (p2.y + p3.y),0);
		return result;
	}
}