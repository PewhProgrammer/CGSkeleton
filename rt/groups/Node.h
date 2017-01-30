#pragma once

#include <vector>
#include <rt\primitive.h>
#include <rt\bbox.h>
#include <stdio.h>

namespace rt{

class Node  {
public:

	int id;
	std::vector<Primitive*> objects;

	BBox boundingBox = BBox::empty();

	Node* right;
	Node* left;
	bool Leaf = false; 

	Node();
	bool isLeaf();

	Intersection searchIntersection(const Ray& r,float previousDistance);
	void add(Primitive* prim);
};

}