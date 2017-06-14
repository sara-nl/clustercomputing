#ifndef __PNGIO_H__
#define __PNGIO_H__

#include <cstdio>
#include <cstdlib>
#include <png.h>
#include "pixel.h"
#include "image.h"

void readpng_version_info();

int read_png(FILE* infile, Image& image);
int write_png(FILE* outfile, const Image& image);

#endif /* __PNGIO_H__ */