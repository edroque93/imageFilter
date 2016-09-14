#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdint.h>

class image {
	public:
		image(uint32_t width, uint32_t height);
		~image();
		
	private:
		uint32_t width, height;
};

#endif