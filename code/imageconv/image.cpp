#include <cstdlib>
#include "image.h"

Image::Image()
: d_height(0), d_width(0), d_bitdepth(0), d_colortype(0)
{
	d_pixels = NULL;
}

Image::Image(size_t height, size_t width, size_t bit_depth, size_t color_type,
		         int interlace_method,	int compression_method,	int filter_method)
: d_height(height), d_width(width), d_bitdepth(bit_depth), d_colortype(color_type),
  d_interlacemethod(interlace_method), d_compressionmethod(compression_method),
  d_filtermethod(filter_method)
{
	alloc_pixels();
}

Image::~Image()
{
	if(d_pixels != NULL)	free_pixels();
}

Image::Image(const Image& other)
{
	d_height = other.d_height;
	d_width = other.d_width;
	d_bitdepth = other.d_bitdepth;
	d_colortype = other.d_colortype;
	d_interlacemethod = other.d_interlacemethod;
	d_compressionmethod = other.d_compressionmethod;
	d_filtermethod = other.d_filtermethod;
	alloc_pixels();

	for(size_t i = 0; i < d_height; i++)
		for(size_t j = 0; j < d_width; j++)
			d_pixels[i][j] = other.d_pixels[i][j];
}

Image& Image::operator=(const Image& other)
{
	d_height = other.d_height;
	d_width = other.d_width;
	d_bitdepth = other.d_bitdepth;
	d_colortype = other.d_colortype;
	d_interlacemethod = other.d_interlacemethod;
	d_compressionmethod = other.d_compressionmethod;
	d_filtermethod = other.d_filtermethod;
	alloc_pixels();

	for(size_t i = 0; i < d_height; i++)
		for(size_t j = 0; j < d_width; j++)
			d_pixels[i][j] = other.d_pixels[i][j];

	return *this;
}

void Image::alloc_pixels()
{
	d_pixels = new Pixel* [d_height];
	for(size_t idx = 0; idx < d_height; idx++)
		d_pixels[idx] = new Pixel [d_width];
}

void Image::free_pixels()
{
	for(size_t idx = 0; idx < d_height; idx++)
		delete [] d_pixels[idx];
	if(d_pixels != NULL)
		delete [] d_pixels;
}