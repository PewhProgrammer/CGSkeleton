#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <rt/groups/group.h>
#include <rt\groups\Node.h>

namespace rt {

class BVH : public Group {
private:

	int NodeNum = 0;

	Primitives SceneObjects;
	Node* Root;
	bool built_flag = false; 
	uint16_t depth;
	uint8_t c_trav = 1;
	uint8_t c_isect = 80;

	virtual void buildTree(Node* node);
	virtual void splitPane(Node* node);
	virtual std::pair<float, float> splitInTheMiddle(Node* node);
	virtual std::pair<float, float> SAH(Node* node);
public:
    BVH();
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
	virtual ~BVH();
    virtual void add(Primitive* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
};

}

#endif
