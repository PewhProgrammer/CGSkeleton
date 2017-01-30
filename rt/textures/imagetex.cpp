#include "imagetex.h"

namespace rt {

	rt::ImageTexture::ImageTexture(const Image & image, BorderHandlingType bh, InterpolationType i)
	{
		this->image = image;
		this->width = this->image.width();
		this->height = this->image.height();

		invHeight = 1.0f / height;
		invWidth = 1.0f / width;

		this->bh = bh;
		this->it = i;
	}

	rt::ImageTexture::ImageTexture(const std::string & filename, BorderHandlingType bh, InterpolationType i)
	{
		this->image.readPNG(filename);
		this->width = this->image.width();
		this->height = this->image.height();

		invHeight = 1.0f / height;
		invWidth = 1.0f / width;

		this->bh = bh;
		//this->bh = BorderHandlingType::MIRROR;
		this->it = i;
		this->filename = filename;
	}


	/*mostly taken from lecture*/
	RGBColor rt::ImageTexture::getColor(const Point & coord)
	{

		float u = (coord.x);
		float v = (coord.y);

		int lu = floor(u); //lattice coordinates
		int lv = floor(v);

		//float fu = fmod(coord.x, 1.0f);
		//float fv = fmod(coord.y, 1.0f);

		float fu = u - lu; 
		float fv = v - lv;

		switch (bh) {
		case CLAMP: {
			fu = (lu >= 1) ? 1 : ((lu < 0) ? 0 : fu);
			fv = (lv >= 1) ? 1 : ((lv < 0) ? 0 : fv);
		}
		break;
		case MIRROR: {
			fu = (abs(lu) % 2 == 1) ? 1 - fu : fu; //neglect pre-sign of value
			fv = (abs(lv) % 2 == 1) ? 1 - fv : fv;
		}
		break;
		case REPEAT:
			/*fu and fv cant turn negative since floor(u) > u if (u is negative) .
			repeatition automatically*/
			//fu = (fu < 0) ? 1 + fu : fu;
			//fv = (fv < 0) ? 1 + fv : fv;
			break;
		}

		/*compute fraction of over texture size*/
		float x = fu * (width - 1);
		float y = fv * (height - 1);


		switch (it) {
		case NEAREST:
			lu = std::min(floor(x), (float)(width - 1));
			lv = std::min(floor(y), (float)(height - 1));

			return image(lu, lv);
		case BILINEAR:
			//fu = x - floor(x);
			//fv = y - floor(y);

			fu = fmod(x, 1.0f);
			fv = fmod(y, 1.0f);

			x = floor(x);
			y = floor(y);

			int X = x + 1;
			int Y = y + 1;

			if (X == width) { //For neighbouring interpolation
				if (bh == MIRROR || bh == CLAMP)
					X = width - 1;
				else if (bh == REPEAT)
					X = X % width;
			}
			if (Y == height) {
				if (bh == MIRROR || bh == CLAMP)
					Y = height - 1;
				else if (bh == REPEAT)
					Y = Y % height;
			}

			if (x > width || y > height) {
				float k = 2; 
			}
			
			return ((1 - fu) * (1 - fv) * image(x, y)
				+ (1 - fu) * (fv)* image(x, Y)
				+ (fu)* (1 - fv) * image(X, y)
				+ (fu)* (fv)* image(X, Y));
		}
	}

	//difference in color , or just gradient
	RGBColor rt::ImageTexture::getColorDX(const Point & coord)
	{
		RGBColor color1 = getColor(coord);
		RGBColor color2 = getColor(Point(coord.x + invWidth, coord.y, coord.z));

		//return color2 - color1;
		return color1 - color2;
	}

	RGBColor rt::ImageTexture::getColorDY(const Point & coord)
	{
		RGBColor color1 = getColor(coord);
		RGBColor color2 = getColor(Point(coord.x, coord.y + invHeight, coord.z));//invHeight corresponds to one unit according to Height

		//return color2 - color1;
		return color1 - color2;
	}
}
