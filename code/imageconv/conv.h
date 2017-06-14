#ifndef __CONV_H__
#define __CONV_H__

#include <vector>
#include "image.h"

Image conv(const Image& image, const std::vector<std::vector<float>> kernel);

#endif /* __CONV_H__ */
