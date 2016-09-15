#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

class image {
	public:
		struct pixel {
			uint16_t A, R, G, B;
		};

		image::pixel **map;
		uint32_t width, height, depth;

		image(uint32_t width, uint32_t height, uint32_t depth);
		~image();

		void initializeMap();
		void applyKernel(int32_t **matrix, uint32_t rows, uint32_t columns);
		void printImage();
};

#endif