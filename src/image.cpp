#include <image.hpp>

image::image(uint32_t width, uint32_t height, uint32_t depth) {
	this->width = width;
	this->height = height;
	this->depth = depth;
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
			map[x][y].A = map[x][y].R = map[x][y].G = map[x][y].B = 0;
		}
	}
}

void image::applyKernel(int32_t **matrix, uint32_t rows, uint32_t columns) {
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			uint32_t acc_R = 0.;
			uint32_t acc_G = 0.;
			uint32_t acc_B = 0.;
			for (size_t j = rows-1; j >= 0; j--) {
				for (size_t i = columns-1; i >= 0; i--) {
					acc_R += matrix[i][j] * map[x-i][y-j].R; //fuck
					//acc_G +=
					//acc_B +=
				}
			}
			// TODO prenormalization?
			map[x][y].R = acc_R;
			map[x][y].G = acc_G;
			map[x][y].B = acc_B;
		}
	}
	return;
}

void image::printImage() {
	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			printf("%d|%d|%d ", map[x][y].R, map[x][y].G, map[x][y].B);
		}
		printf("\n");
	}
}
