#include <vector>
#include <cstdint>
#include "image.h"
#include "pixel.h"

using namespace std;

Image conv(const Image& image, const vector<vector<float>> kernel)
{
	size_t ih, iw, kh, kw;
	size_t height, width, ph, pw;
	Image temp = image;

	// retrieve image and kernel size
	ih = image.getheight();
	iw = image.getwidth();
	kh= kernel.size();
	kw = kernel[0].size();

	// size of the array after padding 0s
	height = ih + kh - 1;
	width = iw + kw - 1;
	// padding height and width on each side of the array
	ph = (kh - 1) / 2;
	pw = (kw - 1) / 2;

	// allocate memory for pixel arrays
	int **red = new int* [height];
	int **green = new int* [height];
	int **blue = new int* [height];
	for(size_t idx = 0; idx < height; idx++)
	{
		red[idx] = new int [width];
		green[idx] = new int [width];
		blue[idx] = new int [width];
	}

	// initialize pixel arrays
	for(size_t i = 0; i < height; i++)
	{
		for(size_t j = 0; j < width; j++)
		{
			red[i][j] = green[i][j] = blue[i][j] = 0;
		}
	}

	// get pixel values of the image
	for(size_t i = 0; i < ih; i++)
	{
		for(size_t j = 0; j < iw; j++)
		{
			red[i+ph][j+pw] = image.getpixel(i, j).getred();
			green[i+ph][j+pw] = image.getpixel(i, j).getgreen();
			blue[i+ph][j+pw] = image.getpixel(i, j).getblue();
		}
	}

	// convolution: apply kernel to image
	float sumred, sumgreen, sumblue;
	temp = image;
	for(size_t i = 0; i < ih; i++)
	{
		for(size_t j = 0; j < iw; j++)
		{
			// reset local sum
			sumred = sumgreen = sumblue = 0.0;
			for(size_t ik = 0; ik < kh; ik++)
			{
				for(size_t jk = 0; jk < kw; jk++)
				{
					sumred += kernel[ik][jk] * red[i+ik][j+jk];
					sumgreen += kernel[ik][jk] * green[i+ik][j+jk];
					sumblue += kernel[ik][jk] * blue[i+ik][j+jk];
				}
			}
		  temp.setpixel(i, j, Pixel(static_cast<uint8_t>(sumred),
		  	            static_cast<uint8_t>(sumgreen), static_cast<uint8_t>(sumblue)));
		}
	}
	
	// free allocated memory
	for(size_t idx = 0; idx < height; idx++)
	{
		delete [] red[idx];
		delete [] green[idx];
		delete [] blue[idx];
	}
	delete [] red;
	delete [] green;
	delete [] blue;

	return temp;
}
