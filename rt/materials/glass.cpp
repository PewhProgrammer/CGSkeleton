#include "glass.h"

namespace rt {
	GlassMaterial::GlassMaterial(float eta)
	{
		this->norm_eta = eta;
		this->inv_eta = 1 / eta;
	}
	RGBColor GlassMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		return RGBColor().rep(0.0f);
	}
	RGBColor GlassMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor().rep(0.0f);
	}
	Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		
		//https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
		float r_par, r_perp, eta,etaT,etaI; 
		Vector adjustedNorm;

		Vector I = -outDir; 
		Vector perfectReflection = (2 * dot(-I, normal)*normal + I).normalize(); // actually already normalized

		float thetaI = dot(normal, I);
		float sinI = sin(acos(thetaI));
	
		//enters medium
		if (thetaI > 0) {
			eta = norm_eta;
			adjustedNorm = -normal;
			etaI = 1; 
			etaT = eta;
		}
		else //leaves medium
		{
			eta = inv_eta;
			adjustedNorm = normal;
			thetaI = -thetaI; 
			etaI = norm_eta;
			etaT = 1;
		}
		//eta is now n1 / n2
		if (sinI > (1 / eta)) // to prevent total internal reflection , snell's law
			return Material::SampleReflectance(perfectReflection, RGBColor(1, 1, 1));


		float thetaT = sqrt(1.0f - (sqr(eta) * (1.0f - sqr(thetaI)))); // square-root of 1 - sine of transmitted angle

		r_perp = (etaT * thetaI - etaI * thetaT) / (etaT * thetaI + etaI * thetaT);
		r_par = (etaT * thetaT - etaI * thetaI) / (etaI * thetaI + etaT * thetaT);

		float fr = 0.5f * (sqr(r_perp) + sqr(r_par));
		float ft = (1.0f - fr)*2; //times 2 to compensate for randomness 

		if (random() < 0.5) // reflection
		{
			return Material::SampleReflectance(perfectReflection, RGBColor::rep(2 * fr)); // why times 2 ?
		}
		else // refraction
		{
			//either eta or its inverse
			Vector vect = I *eta + (eta * thetaI - thetaT) * adjustedNorm; //reflection vector computation
			//Vector vect = I * etaI / etaT + ((etaI / etaT) * thetaI - thetaT) *norm;
			return Material::SampleReflectance(vect, RGBColor::rep(ft)); //times
		}
	}
}