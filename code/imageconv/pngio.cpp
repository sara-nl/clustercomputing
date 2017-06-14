#include <iostream>
#include <png.h>
#include "pngio.h"

void readpng_version_info()
{
    fprintf(stdout, "Compiled with libpng %s; using libpng %s.\n",
      PNG_LIBPNG_VER_STRING, png_libpng_ver);
}

int read_png(FILE* infile, Image& image)
{
	unsigned char sig[8];
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;

	png_uint_32 width, height;
	int bit_depth, color_type;
  int interlace_method, compression_method, filter_method;
  png_bytep *row_pointers;

  
  fread(sig, 1, 8, infile);
  if (!png_check_sig(sig, 8))
      return 1; /* bad signature */

 png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
    return 4;   /* out of memory */

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return 4;   /* out of memory */
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    return 2;
  }

  png_init_io(png_ptr, infile);
  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);

  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 
               &interlace_method, &compression_method, &filter_method);
  Image other(height, width, bit_depth, color_type,
              interlace_method, compression_method, filter_method);
  Pixel pixel;

  // allocate memory for row_pointers
  row_pointers = new png_bytep [height];
  for(size_t idx = 0; idx < height; idx++)
  {
    row_pointers[idx] = new png_byte [png_get_rowbytes(png_ptr, info_ptr)];
  }

  png_read_image(png_ptr, row_pointers);
  // write image data to image
  for(size_t i = 0; i < height; i++)
  {
    for(size_t j = 0; j < width; j++)
    {
      pixel.setred(row_pointers[i][j*4]);
      pixel.setgreen(row_pointers[i][j*4+1]);
      pixel.setblue(row_pointers[i][j*4+2]);
      pixel.setalpha(row_pointers[i][j*4+3]);
      other.setpixel(i, j, pixel);
    }
  }

  image = other;

  // free allocated memory
  for(size_t idx = 0; idx < height; idx++)
    delete [] row_pointers[idx];
  delete [] row_pointers;

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  return EXIT_SUCCESS;
}

int write_png(FILE* outfile, const Image& image)
{
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;

  png_uint_32 height, width;
  png_bytep *row_pointers;

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
    return 4;   /* out of memory */

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return 4;   /* out of memory */
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return 2;
  }

  // set image attributes
  width = image.getwidth();
  height = image.getheight();
  png_set_IHDR(png_ptr,
               info_ptr,
               width,
               height,
               image.getbitdepth(),
               image.getcolortype(),
               image.getinterlacemethod(),
               image.getcompressionmethod(),
               image.getfiltermethod());

  // allocate memory for row_pointers
  row_pointers = new png_bytep [height];
  for(size_t idx = 0; idx < height; idx++)
  {
    row_pointers[idx] = new png_byte [4 * width * sizeof(uint8_t)];
  }

  for(size_t i = 0; i < height; i++)
  {
    for(size_t j = 0; j < width; j++)
    {
      row_pointers[i][j*4] = (png_byte)image.getpixel(i,j).getred();
      row_pointers[i][j*4+1] = (png_byte)image.getpixel(i,j).getgreen();
      row_pointers[i][j*4+2] = (png_byte)image.getpixel(i,j).getblue();
      row_pointers[i][j*4+3] = (png_byte)image.getpixel(i,j).getalpha();
    }
  }

  // write the image data to "outfile"
  png_init_io (png_ptr, outfile);
  png_set_rows (png_ptr, info_ptr, row_pointers);
  png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  // End write
  png_write_end(png_ptr, NULL);

  // free allocated memory
  for(size_t idx = 0; idx < height; idx++)
    delete [] row_pointers[idx];
  delete [] row_pointers;

  png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png_ptr, (png_infopp)NULL);

  return EXIT_SUCCESS;
}