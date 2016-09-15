#include <image.hpp>

image::image(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	map = (image::pixel **) malloc(width * sizeof(image::pixel *));
	for (uint32_t i = 0; i < width; i++) {
		map[i] = (image::pixel *) malloc(height * sizeof(image::pixel));
	}
	initializeMap();
}

image::~image() {
	for (uint32_t i = 0; i < width; i++) {
		free(map[i]);
	}
	free(map);
}

void image::initializeMap() {
	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			map[x][y].R = map[x][y].G = map[x][y].B = 0;
		}
	}
}

void image::applyKernel(int32_t **matrix, int32_t rows, int32_t columns) {
	return;
}
