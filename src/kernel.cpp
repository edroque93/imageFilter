#include <kernel.hpp>

kernel::kernel(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	matrix = (int32_t **) malloc(width * sizeof(int32_t *));
	for (uint32_t i = 0; i < width; i++) {
		matrix[i] = (int32_t *) malloc(height * sizeof(int32_t));
	}
	initializeMatrix();
}

kernel::~kernel() {
	for (uint32_t i = 0; i < width; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void kernel::initializeMatrix() {
	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			matrix[x][y] = 0;
		}
	}
}
