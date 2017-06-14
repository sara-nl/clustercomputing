#ifndef __PIXEL_H__
#define __PIXEL_H__

#include <cstdlib>
#include <cstdint>

class Pixel
{
public:
	Pixel();
	Pixel(uint8_t red, uint8_t green, uint8_t blue);
	~Pixel();
	Pixel(const Pixel& other);
	Pixel& operator=(const Pixel& other);

	Pixel operator*(int val);

	inline void setred(uint8_t red) { d_red = red; };
	inline void setgreen(uint8_t green) { d_green = green; };
	inline void setblue(uint8_t blue) { d_blue = blue; };
	inline void setalpha(uint8_t alpha) { d_alpha = alpha; };
	inline uint8_t getred() const { return d_red; };
	inline uint8_t getgreen() const { return d_green; };
	inline uint8_t getblue() const { return d_blue; };
	inline uint8_t getalpha() const { return d_alpha; };
	
private:
	uint8_t d_red;
	uint8_t d_green;
	uint8_t d_blue;
	uint8_t d_alpha;
};

#endif /* __PIXEL_H__ */