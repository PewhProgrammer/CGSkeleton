#ifndef CG1RAYTRACER_TEXTURES_PERLIN_HEADER
#define CG1RAYTRACER_TEXTURES_PERLIN_HEADER

#include <core/vector.h>

#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/scalar.h>

#include <vector>

typedef std::pair<float, float> f2; 

namespace rt {

    class PerlinTexture : public Texture {
	private:
		std::vector<f2> octaves; 
		RGBColor black, white;
		virtual float interpolateTo0_1(float x);
    public:
        PerlinTexture(const RGBColor& white, const RGBColor& black);
        void addOctave(float amplitude, float frequency);
        virtual RGBColor getColor(const Point& coord);
        virtual RGBColor getColorDX(const Point& coord);
        virtual RGBColor getColorDY(const Point& coord);
    };

}

#endif
