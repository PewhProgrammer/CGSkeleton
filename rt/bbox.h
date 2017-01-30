#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>

#include <map>
#include <rt\intersection.h>
#include <rt\solids\infiniteplane.h>

namespace rt {

class Ray;

class BBox {
public:
    Point min, max;

    BBox() {}
    BBox(const Point& min, const Point& max) {
		this->min = min;
		this->max = max;
	}
    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const { return max - min; }

    std::pair<float,float> intersect(const Ray& ray) const;

    bool isUnbound();
};

}


#endif
