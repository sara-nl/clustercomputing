#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include "image.h"

Image sharpen(const Image& image);
Image edge(const Image& image);
Image identical(const Image& image);
Image gsmoothing(const Image& image);
Image verify_result(const Image& image);

#endif /* __UTIL_H__ */