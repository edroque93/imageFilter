#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdint.h>
#include <stdlib.h>

template <typename T>
class image {
	public:
		struct pixel {
			T R, G, B;
		};

		image::pixel **map;
		uint32_t width, height;

		image(uint32_t width, uint32_t height);
		~image();

		void initializeMap();
		void applyKernel(int32_t **matrix, int32_t rows, int32_t columns);
};

#endif