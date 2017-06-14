#include "pixel.h"

Pixel::Pixel() {}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue)
: d_red(red), d_green(green), d_blue(blue)
{
	d_alpha = 0;
}

Pixel::~Pixel() {}

Pixel::Pixel(const Pixel& other)
: d_red(other.d_red), d_green(other.d_green), 
  d_blue(other.d_blue), d_alpha(other.d_alpha)
{}

Pixel& Pixel::operator=(const Pixel& other)
{
	d_red = other.d_red;
	d_green = other.d_green;
	d_blue = other.d_blue;
	d_alpha = other.d_alpha;
	return *this;
}

Pixel Pixel::operator*(int val)
{
	Pixel pixel;
	pixel.d_red = this->d_red * val;
	pixel.d_green = this->d_green * val;
	pixel.d_blue = this->d_blue * val;
	pixel.d_alpha = this->d_alpha * val;
	return pixel;
}
