#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdint.h>
#include <stdlib.h>

class image {
	public:
		struct pixel {
			uint8_t R, G, B;
		};

		image::pixel **map;

		image(uint32_t width, uint32_t height);
		~image();

		void initializeMap();
		//void applyFilter
		
	private:
		uint32_t width, height;
};

#endif