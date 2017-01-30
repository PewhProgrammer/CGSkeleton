#include "constant.h"

namespace rt {

	rt::ConstantTexture::ConstantTexture(const RGBColor & color)
	{
		this->color = color;
	}

	RGBColor rt::ConstantTexture::getColor(const Point & coord)
	{
		return color;
	}

	RGBColor rt::ConstantTexture::getColorDX(const Point & coord)
	{
		NOT_IMPLEMENTED;
	}

	RGBColor rt::ConstantTexture::getColorDY(const Point & coord)
	{
		NOT_IMPLEMENTED;
	}

}
