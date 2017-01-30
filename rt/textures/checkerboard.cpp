#include "checkerboard.h"

namespace rt {
	CheckerboardTexture::CheckerboardTexture(const RGBColor & white, const RGBColor & black)
	{
		this->white = white;
		this->black = black;
	}
	RGBColor CheckerboardTexture::getColor(const Point & coord)
	{
		//x,y,z 

		float u, v, w;
		u = fmod(coord.x, 1.0f);
		w = fmod(coord.y, 1.0f);
		v = fmod(coord.z, 1.0f);

		uint8_t latX, latY, latZ;

		//note, different behavior for zero axis

		if (u >= 0) 
			latX = u < 0.5f ? 0 : 1; 
		else 
			latX = u > -0.5f ? 1 : 0; 

		if (w >= 0)
			latY = w < 0.5f ? 0 : 1;
		else
			latY = w > -0.5f ? 1 : 0; 

		if (v >= 0)
			latZ = v > 0.5f ? 0 : 1;
		else
			latZ = v < -0.5f ? 1 : 0; 

		int parity = (latX+latY+latZ);

		if (parity == 0 || parity == 2)
			return black;
		else 
			return white;
	}
	RGBColor CheckerboardTexture::getColorDX(const Point & coord)
	{
		return RGBColor();
	}
	RGBColor CheckerboardTexture::getColorDY(const Point & coord)
	{
		return RGBColor();
	}
}