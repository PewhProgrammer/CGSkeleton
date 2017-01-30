#include "spherical.h"

namespace rt {
	SphericalCoordMapper::SphericalCoordMapper()
	{
	}

	/* src:Fundamentals of Computer Graphics
	http://keisan.casio.com/exec/system/1359533867*/
	SphericalCoordMapper::SphericalCoordMapper(const Point & origin, const Vector & zenith, const Vector & azimuthRef)
	{
		/* same procedure as in cylindrical 
		Distort both values u,v with cylindrical coordinates
		this is called radial projection*/
		this->origin = origin;
		zen = zenith.normalize();

		radial_distx = 1 / azimuthRef.length(); // in [0,1]
		radial_disty = 1 / zenith.length();
		Vector z_axis; 

		z_axis = zen;
		y_axis = cross(zenith, azimuthRef).normalize();
		x_axis = cross(y_axis, zenith).normalize(); 

		/*this->y_axis = cross(z_axis, azimuthRef).normalize();
		this->x_axis = cross(y_axis, z_axis).normalize();*/

		this->projectionMatrix = Matrix::system(x_axis, y_axis, z_axis);
		this->projectionMatrix = projectionMatrix.transpose();
		this->projectionMatrix = projectionMatrix.invert();
		this->kai = Matrix::system(x_axis, y_axis, cross(x_axis, y_axis));

		zen = projectionMatrix * zen;
	}

	Point rt::SphericalCoordMapper::getCoords(const Intersection & hit) const
	{
		float u, v;
		//Vector f4 = this->projectionMatrix *  Float4(hit.local() - origin); //transformed
		Vector polar_vec = this->projectionMatrix *  (hit.local() - origin);
		Vector polar_vecN(polar_vec.normalize());
		/*float theta_x = dot(polar_vecN, x_axis);
		float phi_y = dot(polar_vecN,y_axis);


		Vector polar_vec_In2D = Vector(theta_x, phi_y, 0.0f).normalize();

		//defined as span angle x and z or azimuth angle
		float polar_angle = atan(polar_vec_In2D.y / polar_vec_In2D.x);
		//y texture is now being influenced by an angle aswell
		float zenith_angle = acos(phi_y); 
		//phi_y = 1 - phi_y; 
		//zenith_angle = acos(abs(phi_y));
		//polar_angle = pi + (atan(-polar_vec_In2D.x / polar_vec_In2D.y)); */

		float phi_y = dot(polar_vecN, zen);

		float polar_angle = atan(polar_vec.y /polar_vec.x);
		float zenith_angle = acos(phi_y);

		u = polar_angle / (2 * pi); // as in lecture slides
		v = zenith_angle / pi;


		return Point(u * radial_distx, v * radial_disty, 0);
	}
}