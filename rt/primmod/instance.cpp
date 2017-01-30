#include "instance.h"

namespace rt {

	Instance::Instance(Primitive* content) {
		cont = content;
		transMatrix = Matrix::identity();
		invTransMatrix = Matrix::identity();

		
		//get rough bounds
		Point p = content->getBounds().max;
		Point q = content->getBounds().min;

		//compute mid point of bounds and take most distant point from outer bounds to mid
		//to enlarge the box 
		Vector midVector = content->getBounds().diagonal() * 0.5f;
		float length = midVector.length() * 2;
		Point mid = content->getBounds().min + midVector; 

		this->bounds.max = Point(mid.x + length, mid.y + length, mid.z + length);
		this->bounds.max = Point(mid.x - length, mid.y - length, mid.z - length);
	}

	Primitive * Instance::content()
	{
		return cont;
	}
	void Instance::reset()
	{
		transMatrix =  Matrix::identity();
	}
	void Instance::translate(const Vector & t)
	{
		//float c = .7f;
		transMatrix[0][3] += t.x;
		transMatrix[1][3] += t.y;
		transMatrix[2][3] += t.z;

		invTransMatrix = transMatrix.invert();

		bounds.max = bounds.max + t; 
		bounds.min = bounds.min + t;
	}
	// taken from
	//https://en.wikipedia.org/wiki/Rotation_group_SO(3)
	void Instance::rotate(const Vector & axis, float angle)
	{
		//rotation around some axis
		Vector axisNormal = axis.normalize();

		float u = axisNormal.x;
		float v = axisNormal.y;
		float w = axisNormal.z;

		float a = axis.x;
		float b = axis.y;
		float c = axis.z;

		Float4 c1 = Float4(
			sqr(u) + (sqr(v) + sqr(w))*cos(angle),
			u*v*(1 - cos(angle)) + w*sin(angle),
			u*w*(1 - cos(angle)) - v*sin(angle), 0);

		Float4 c2 = Float4(
			u*v*(1 - cos(angle)) - w*sin(angle), 
			sqr(v) + (sqr(u) + sqr(w))*cos(angle),
			v*w*(1 - cos(angle)) + u*sin(angle), 0);

		Float4 c3 = Float4(
			u*w*(1 - cos(angle)) + v*sin(angle),
			v*w*(1 - cos(angle)) - u*sin(angle),
			sqr(w) + (sqr(u) + sqr(v))*cos(angle), 0);

		Float4 c4 = Float4(
			(a*(sqr(v) + sqr(w)) - u*(b*v + c*w))*(1 - cos(angle)) + (b*w - c*v)*sin(angle), 
			(b*(sqr(u) + sqr(w)) - v*(a*u + c*w))*(1 - cos(angle)) + (c*u - a*w)*sin(angle),
			(c*(sqr(u) + sqr(v)) - w*(a*u + b*v))*(1 - cos(angle)) + (a*v - b*u)*sin(angle), 1);


		Matrix rotationMatrix(
			c1,
			c2,
			c3,
			c4);

		transMatrix = product(transMatrix, rotationMatrix);
		invTransMatrix = transMatrix.invert();

		//bounds computation not needed since we computed rougher bounds in constructor

	}
	void Instance::scale(float scale)
	{
		//scale = scale * 2; 

		transMatrix[0][0] *= scale;
		transMatrix[1][1] *= scale;
		transMatrix[2][2] *= scale;

		invTransMatrix = transMatrix.invert();

		//Bounds computation
		Vector midVector = bounds.diagonal() * 0.5f;
		float length = midVector.length() * scale; 
		
		Point mid = bounds.min + midVector;

		this->bounds.max = Point(mid.x + length, mid.y + length, mid.z + length);
		this->bounds.max = Point(mid.x - length, mid.y - length, mid.z - length);

	}
	void Instance::scale(const Vector & scale)
	{
		Matrix scaleMatrix = Matrix::identity();
		//naively assuming scale is first operation
		/*transMatrix[0][0] = scale.x;
		transMatrix[1][1] = scale.y;
		transMatrix[2][2] = scale.z;*/

		scaleMatrix[0][0] = scale.x; 
		scaleMatrix[1][1] = scale.y;
		scaleMatrix[2][2] = scale.z;

		transMatrix = product(scaleMatrix,transMatrix);

		invTransMatrix = transMatrix.invert();

		//Bounds computation
		Vector midVector = bounds.diagonal() * 0.5f;
		float length = midVector.length() * scale.length();

		Point mid = bounds.min + midVector;

		this->bounds.max = Point(mid.x + length, mid.y + length, mid.z + length);
		this->bounds.max = Point(mid.x - length, mid.y - length, mid.z - length);

	}
	BBox Instance::getBounds() const
	{
		return this->bounds;
	}
	Intersection Instance::intersect(const Ray & ray, float previousBestDistance) const
	{
		//transform ray and intersect original object
		Ray transformedRay = ray;
		Float4 o(ray.o);
		Float4 d(ray.d);

		transformedRay.o = Point(invTransMatrix * o);
		transformedRay.d = Vector(invTransMatrix * d).normalize();

		Intersection it = cont->intersect(transformedRay, previousBestDistance);
		float newPrevDistance = it.distance; 

		if (!it)
			return Intersection::failure();

		//normal computation is result of transpose of inverted Transformation matrix
		return Intersection(
			newPrevDistance, ray, it.solid,
			(invTransMatrix.transpose()* it.normal()).normalize()
			, transMatrix * it.hitPoint());

	}
	void Instance::setMaterial(Material * m)
	{
		NOT_IMPLEMENTED;
	}
	void Instance::setCoordMapper(CoordMapper * cm)
	{
		NOT_IMPLEMENTED;
	}
}