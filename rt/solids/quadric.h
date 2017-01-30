#ifndef CG1RAYTRACER_SOLIDS_QUADRIC_HEADER
#define CG1RAYTRACER_SOLIDS_QUADRIC_HEADER

#include <rt/solids/solid.h>

#include <rt\intersection.h>
#include <rt\bbox.h>

namespace rt {

	class Quadric : public Solid {
	private:
		float A, B, C, D, E, F, G, H, I, J;
		Vector computeNormal(const Point& hit) const;
	public:
		Quadric() {}
		Quadric(float A, float B, float C, float D, float E,
			float F, float G, float H, float I, float J, CoordMapper* texMapper, Material* material)
			:A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J) {
			this->texMapper = texMapper; 
			this->material = material; 
		}

		virtual BBox getBounds() const;
		virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
		virtual Point sample() const;
		virtual float getArea() const;
	};

}

#endif
