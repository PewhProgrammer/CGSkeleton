#include "quadric.h"

namespace rt {
	BBox Quadric::getBounds() const
	{
		return BBox(Point().rep(-FLT_MAX), Point().rep(FLT_MAX));
	}
	Intersection Quadric::intersect(const Ray & ray, float previousBestDistance) const
	{
		//F(x, y, z) = Ax2 + By2 + Cz2 + Dxy + Exz + Fyz + Gx + Hy + Iz + J = 0
		/*
		at^2 + bt + c = 0 with

		a = Axd2 + Byd2 + Czd2 + Dxdyd + Exdzd + Fydzd

		b = 2*Axoxd + 2*Byoyd + 2*Czozd + D(xoyd + yoxd) + E(xozd + zoxd) + F(yozd + ydzo) + Gxd + Hyd + Izd

		c = Axo2 + Byo2 + Czo2 + Dxoyo + Exozo + Fyozo + Gxo + Hyo + Izo + J

		This leads to the solutions:
		t0 =( - Bq - ((Bq2 - 4AqCq))^0.5)/ 2Aq
		t1 =( - Bq + ((Bq2 - 4AqCq))^0.5)/ 2Aq
		*/

		Point hit; Vector normal; 

		float dx = ray.d.x; float dy = ray.d.y; float dz = ray.d.z; 
		float ox = ray.o.x; float oy = ray.o.y; float oz = ray.o.z;

		float a = A*sqr(dx) + B*sqr(dy) + C*sqr(dz) + D*dx*dy + E*dx*dz + F*dy*dz;
		float b = 2 * A*ox*dx + 2 * B*oy*dy + 2 * C*oz*dz + D*(ox*dy + oy*dx) + E*(ox*dz) + F*(oy*dz + dy*oz) +
			G*dx + H*dy + I*dz;
		float c = A*sqr(ox) + B*sqr(oy) + C*sqr(oz) + D*ox*oy + E*ox*oz + F*oy*oz + G*ox + H*oy + I*oz + J;

		float t,t1;

		if (a == 0) { // return for one solution
			t = -c / b; 
			hit = ray.o + ray.d*t;
			normal = computeNormal(hit);

			return Intersection(t, ray, this, normal, Point());
		}
		float radiator = sqr(b) - 4 * a*c;  
		if (radiator < 0.f) return Intersection::failure();

		t = (-b + sqrt(radiator)) / (2 * a);	
		t1 = (-b - sqrt(sqr(b) - 4 * a*c)) / (2 * a); // t1 guaranteed smaller than t

		if (t1 > 0) t = t1;  //so t1 is positive 
		else if (t <= 0) return Intersection::failure();
		// here we know for sure t > 0, we have our t

		/*
		normal computation 
		xn = 2*A*xi + D*yi + E*zi + G
		yn = 2*B*yi + D*xi + F*zi + H
		z n = 2*C*zi + E*xi + F*yi + I
		*/

		hit = ray.o + ray.d*t; 
		normal = computeNormal(hit);

		return Intersection(t, ray, this, normal, Point());
	}

	Point Quadric::sample() const
	{
		NOT_IMPLEMENTED;
	}

	float Quadric::getArea() const
	{
		NOT_IMPLEMENTED;
	}

	Vector Quadric::computeNormal(const Point& hit) const {
		float xi = hit.x; float yi = hit.y; float zi = hit.z;

		float nx = 2 * A*xi + D*yi + E*zi + G;
		float ny = 2 * B*yi + D*xi + F*zi + H;
		float nz = 2 * C*zi + E*xi + F*yi + I;

		return Vector(nx, ny, nz);
	}
}