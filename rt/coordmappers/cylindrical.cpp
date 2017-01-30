#include "cylindrical.h"

namespace rt {
	/* transform cartesian to cylindrical system 
	   Textures slides 52
	   http://courses.cs.vt.edu/~cs4204/lectures/texture_mapping.pdf : page 18
	   http://keisan.casio.com/exec/system/1359534107*/
	CylindricalCoordMapper::CylindricalCoordMapper(const Point & origin, const Vector & longitudinalAxis, const Vector & polarAxis)
	{
		//longitudinal is y dir
		//longitudinal and polar not necessarily orthogonal (1)

		Vector z_dir = cross(longitudinalAxis, polarAxis);

		radial_disty = 1.0f / longitudinalAxis.length(); //scaling factor in [0,1]
		radial_distx = 1.0f / polarAxis.length();

		y_axis = cross(longitudinalAxis, polarAxis).normalize(); // since (1) create new axis s.t. we have cartesian
		x_axis = cross(longitudinalAxis, y_axis).normalize();    //polarAxis is defined to be x-axis but have to "re-orient" it. either left or right sided depended on y_axis

		this->origin = origin;
		this->longitudinalAxis = longitudinalAxis.normalize();
	}

	Point rt::CylindricalCoordMapper::getCoords(const Intersection & hit) const
	{
		/* pair of coordinates (dist, polar_axis) */

		float u, v; 
		Vector polar_vec(hit.local() - origin); //vector from pol to hit: drop p
		Vector polar_vecN(polar_vec.normalize());
		float theta_x = dot(polar_vecN, x_axis);
		float phi_y = dot(polar_vecN, y_axis);

		//float check2 = dot(polar_vec.normalize(), longitudinalAxis);

		// p = sqrt(sqr(x) + sqr(y))
		//theta_x = polar_vec.x;
		//phi_y = polar_vec.y;
		Vector polar_vec_In2D = Vector(theta_x, phi_y, 0.0f).normalize(); //describes a vector with same angular value as theta and phi
		float polar_angle = atan(polar_vec_In2D.y / polar_vec_In2D.x); //angle alpha of projection and x_axis

		//z = v/h
		//texture v increases in longitudinalAxis
		v = dot(polar_vec,longitudinalAxis); // dot projection
		u = polar_angle / (2 * pi);  // map u

		//return Point(v * radial_disty,u * radial_distx, 0);
		return Point(u * radial_distx, v * radial_disty, 0);
	}
}