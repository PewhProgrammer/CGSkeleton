#include <rt/textures/perlin.h>
#include <core/point.h>
#include <core/interpolate.h>
#include <core/scalar.h>

namespace rt {

namespace {

    /* returns a value in range -1 to 1 */
    float noise(int x, int y, int z) {
        int n = x + y * 57 + z * 997;
        n = (n<<13) ^ n;
        return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }

}
/* returns a value in range [0,1] from [-1,1]*/
float PerlinTexture::interpolateTo0_1(float x)
{
	return (x + 1)*(0.5f);
}

PerlinTexture::PerlinTexture(const RGBColor & white, const RGBColor & black)
{
	this->white = white;
	this->black = black;
}

void PerlinTexture::addOctave(float amplitude, float frequency)
{
	std::pair<float, float> pair(amplitude, frequency);
	octaves.push_back(pair);
}

RGBColor PerlinTexture::getColor(const Point & coord)
{

	float weight = 0.0f;
	float inpolPoint3D, xWeight, yWeight, zWeight;

	int x, y, z; 
	float x0y0z0, x1y0z0, x0y0z1, x1y0z1; //bottom
	float x0y1z0, x1y1z0, x0y1z1, x1y1z1; //top

	for (f2 oct : octaves) {

		Point altered_coord = coord * oct.second;
		x = floor(altered_coord.x);
		y = floor(altered_coord.y);
		z = floor(altered_coord.z);

		//basically describes a 3 dimensional room of axis length max. 2
		//interpolate data point from bottom
		x0y0z0 = interpolateTo0_1(noise(x, y, z));
		x1y0z0 = interpolateTo0_1(noise(x + 1, y, z));
		x0y0z1 = interpolateTo0_1(noise(x, y, z + 1));
		x1y0z1 = interpolateTo0_1(noise(x + 1, y, z + 1));

		//interpolate data point from top
		x0y1z0 = interpolateTo0_1(noise(x, y + 1, z));
		x1y1z0 = interpolateTo0_1(noise(x + 1, y + 1, z));
		x0y1z1 = interpolateTo0_1(noise(x, y + 1, z + 1));
		x1y1z1 = interpolateTo0_1(noise(x + 1, y + 1, z + 1));

		xWeight = fmod(altered_coord.x, 1.0f);
		yWeight = fmod(altered_coord.y, 1.0f);
		zWeight = fmod(altered_coord.z, 1.0f);

		//xWeight has to be in range [0,1]
		xWeight = xWeight > 0 ? xWeight : 1 + xWeight; 
		yWeight = yWeight > 0 ? yWeight : 1 + yWeight;
		zWeight = zWeight > 0 ? zWeight : 1 + zWeight;

		inpolPoint3D = lerp3d(x0y0z0, x1y0z0, x0y1z0,x1y1z0, x0y0z1, x1y0z1, x0y1z1, x1y1z1, xWeight, yWeight, zWeight);
		weight += inpolPoint3D * oct.first;
	}

	RGBColor value = lerp(black, white, weight);
	return value;
}

RGBColor PerlinTexture::getColorDX(const Point & coord)
{
	NOT_IMPLEMENTED;
}

RGBColor PerlinTexture::getColorDY(const Point & coord)
{
	NOT_IMPLEMENTED;
}

}
