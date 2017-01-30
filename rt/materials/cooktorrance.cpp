#include "cooktorrance.h"

namespace rt {
	CookTorrance::CookTorrance(float eta, float kappa,float m, Texture * diffuse, Texture * specular)
	{
		this->specular = specular;
		this->diffuse = diffuse;
		this->eta = eta;
		this->kappa = kappa;
		this->m = m; 

	}
	RGBColor rt::CookTorrance::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
	{
		/* sum over diffuse and specular term*/
		/* taken from lecture slides*/

		//precompute values
		float NI_angle = abs(dot(normal, inDir));
		float NV_angle = abs(dot(normal, outDir)); //check if outDir is indeed normalized : yes it is
		//H = (L + V) / |L + V|
		Vector H = (-inDir + outDir).normalize();
		float NH_angle = abs(dot(normal, H));
		float VH_angle = abs(dot(outDir, H));

		//compute diffuse term
		RGBColor diffuse_term = RGBColor().rep(NI_angle) * diffuse->getColor(texPoint)*invPi;

		//compute fresnel term
		//parallel light
		float r_par =
			((sqr(eta) + sqr(kappa))*sqr(NI_angle) - 2.0f * eta*NI_angle + 1.0f)
			/ ((sqr(eta) + sqr(kappa))*sqr(NI_angle) + 2.0f * eta*NI_angle + 1.0f);

		//perpendicular light
		float r_perp =
			((sqr(eta) + sqr(kappa)) - 2.0f * eta*NI_angle + sqr(NI_angle))
			/ ((sqr(eta) + sqr(kappa)) + 2.0f * eta*NI_angle + sqr(NI_angle));

		//unpolarized light
		float F = (r_par + r_perp) * 0.5f; 

		//compute Distribution Function of microfacte orientations
		/*D, statical probability of microfacets oriented towards specular vector H.*/
		float alpha_degree = acos(NH_angle); // in radians
		float gaussian = exp(-sqr(tan(alpha_degree)/m));
		float D = gaussian / (pi * sqr(m) * pow(cos(alpha_degree), 4));

		//compute Geometric Attenuation
		float par_mask = (2*NH_angle*NI_angle) / VH_angle;
		float shadow_mask = (2*NH_angle*NV_angle) / VH_angle;  
		float G = min(1.0f, min(par_mask, shadow_mask));

		float k_s = (F*D*G) / ( NV_angle * NI_angle); //pi is in diffuse term already(?)
		//not sure if multiplied with normalization
		RGBColor specular_term = RGBColor().rep(k_s) * specular->getColor(texPoint);

		return diffuse_term + specular_term;
	}

	RGBColor rt::CookTorrance::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return RGBColor().rep(.0f);
	}

	Material::SampleReflectance rt::CookTorrance::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
	{
		return SampleReflectance(Vector().rep(.0f),RGBColor().rep(.0f));
	}

	Material::Sampling rt::CookTorrance::useSampling() const
	{
		return Material::SAMPLING_NOT_NEEDED;
	}
}