#include "plane.h"

namespace rt {
	PlaneCoordMapper::PlaneCoordMapper(const Vector & e1, const Vector & e2)
	{
		Vector e3 = cross(e1, e2);
		/*
		e1.x e2.x e3.x 0
		e1.y e2.y e3.y 0
		e1.z e2.z e3.z 0
		0    0    0    0
		*/

		Projection = Matrix::system(e1, e2, e3).transpose(); // switch up rows/columns since system is creating wrong matrix
		Projection = Projection.invert();
	}
	Point PlaneCoordMapper::getCoords(const Intersection & hit) const
	{
		float x, y, z; 
		Point local = hit.local();
		Float4 f4 = Projection * Float4(local);

		x = f4[0];
		y = f4[1];
		z = 0; //drop z 
		return Point(x,y,z);
	}
}