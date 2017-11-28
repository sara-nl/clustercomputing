#ifndef __Image_H__
#define __Image_H__

#include "pixel.h"

class Image
{
public:
	Image();
	Image(size_t height, size_t width, size_t bit_depth, size_t color_type,
		    int interlace_method,	int compression_method,	int filter_method);
	~Image();

	Image(const Image& other);
	Image& operator=(const Image& other);

	inline void setpixel(size_t x, size_t y, Pixel pixel) { d_pixels[x][y] = pixel; };
  inline void setheight(size_t height) { d_height = height; };
  inline void setwidth(size_t width) { d_width = width; };
  inline void setbitdepth(size_t bitdepth) { d_bitdepth = bitdepth; };
  inline void setcolortype(size_t colortype) { d_colortype = colortype; };
  inline void setinterlacemethod(int interlacemethod) { d_interlacemethod = interlacemethod; };
  inline void setcompressionmethod(int compressionmethod) { d_compressionmethod = compressionmethod; };
  inline void setfiltermethod(int filtermethod) { d_filtermethod = filtermethod; };

	inline Pixel getpixel(size_t x, size_t y) const { return d_pixels[x][y]; };
	inline size_t getheight() const { return d_height; };
	inline size_t getwidth() const { return d_width; };
	inline size_t getbitdepth() const { return d_bitdepth; };
	inline size_t getcolortype() const { return d_colortype; };
	inline int getinterlacemethod() const { return d_interlacemethod; };
	inline int getcompressionmethod() const { return d_compressionmethod; };
	inline int getfiltermethod() const { return d_filtermethod; };

private:
	Pixel **d_pixels;
	size_t d_height;
	size_t d_width;
	size_t d_bitdepth;
	size_t d_colortype;
	int d_interlacemethod;
	int d_compressionmethod;
	int d_filtermethod;

	void alloc_pixels();
	void free_pixels();
};

#endif /* __Image_H__ */