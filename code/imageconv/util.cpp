#include <iostream>
#include <vector>
#include "util.h"
#include "image.h"
#include "conv.h"

using namespace std;

Image sharpen(const Image& image)
{
	Image temp;

	vector<vector<float>> kernel = {
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};

	temp = conv(image, kernel);

	return temp;
}

Image edge(const Image& image)
{
	Image temp;

	vector<vector<float>> kernel = {
		{-1, -1, -1},
		{-1, 8, -1},
		{-1, -1, -1}
	};

	temp = conv(image, kernel);

	return temp;
}
Image identical(const Image& image)
{
	Image temp;

	vector<vector<float>> kernel = {
		{0, 0, 0},
		{0, 1, 0},
		{0, 0, 0}
	};

	temp = conv(image, kernel);

	return temp;
}

Image gsmoothing(const Image& image)
{
	Image temp;

	vector<vector<float>> kernel = {
		{1, 4, 7, 4, 1},
		{4, 16, 26, 16, 4},
		{7, 26, 41, 26, 7},
		{4, 16, 26, 16, 4},
		{1, 4, 7, 4, 1}
	};

	for(size_t ik = 0; ik < kernel.size(); ik++)
		for(size_t jk = 0; jk < kernel[0].size(); jk++)
			kernel[ik][jk] /= 273.0;

	temp = conv(image, kernel);

	return temp;
}

Image verify_result(const Image& image)
{
	Image temp = image;
	Pixel pixel;
	for(size_t i = 0; i < temp.getheight(); i++)
	{
		for(size_t j = 0; j < temp.getwidth(); j++)
		{
			pixel = temp.getpixel(i, j) * 1;
			temp.setpixel(i, j, pixel);
		}
	}
	return temp;
}