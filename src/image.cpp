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

image *image::applyKernel(kernel *k) {
	image *result = new image(width, height, depth);
	uint8_t radix = k->width/2;
	if (k->height/2 != radix) {
		ERROR("image::applyKernel: wrong matrix dimension.");
	}
	for (int64_t y = 0; y < height; y++) {
		for (int64_t x = 0; x < width; x++) {
			double acc_R = 0.;
			double acc_G = 0.;
			double acc_B = 0.;
			for (int j = k->height-1; j >= 0; j--) {
				for (int i = k->width-1; i >= 0; i--) {
					double kernelNormalized = (double) k->matrix[i][j]/k->divisor;
					int64_t realY = y-j+radix;
					int64_t realX = x-i+radix;
					if (realX < 0) {
						realX = 0;
					}
					if (realX >= width) {
						realX = width-1;
					}
					if (realY < 0) {
						realY = 0;
					}
					if (realY >= height) {
						realY = height-1;
					}
					acc_R += kernelNormalized * (double) map[realX][realY].R;
					acc_G += kernelNormalized * (double) map[realX][realY].G;
					acc_B += kernelNormalized * (double) map[realX][realY].B;
				}
			}
			result->map[x][y].R = acc_R;
			result->map[x][y].G = acc_G;
			result->map[x][y].B = acc_B;
		}
	}
	return result;
}

image *image::applyKernel(int32_t **matrix, uint32_t rows, uint32_t columns) {
	image *result = new image(width, height, depth);
	uint8_t radix = rows/2;
	if (columns/2 != radix) {
		ERROR("image::applyKernel: wrong matrix dimension.");
	}
	printf("%d\n", radix);
	int32_t matrixSum = 0;
	for (size_t y = 0; y < rows; y++) {
		for (size_t x = 0; x < columns; x++) {
			matrixSum += matrix[x][y];
		}
	}
	for (size_t y = 2; y < height-2; y++) {
		for (size_t x = 2; x < width-2; x++) {
			double acc_R = 0.;
			double acc_G = 0.;
			double acc_B = 0.;
			for (int j = rows-1; j >= 0; j--) {
				for (int i = columns-1; i >= 0; i--) {
					double kernelNormalized = matrix[i][j]/(double) matrixSum;
					acc_R += kernelNormalized * (double) map[x-i+radix][y-j+radix].R;
					acc_G += kernelNormalized * (double) map[x-i+radix][y-j+radix].G;
					acc_B += kernelNormalized * (double) map[x-i+radix][y-j+radix].B;
				}
			}
			result->map[x][y].R = acc_R;
			result->map[x][y].G = acc_G;
			result->map[x][y].B = acc_B;
		}
	}
	return result;
}

image *image::substractImage(image *img) {
	image *result = new image(width, height, depth);
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			result->map[x][y].R = map[x][y].R - img->map[x][y].R;
			result->map[x][y].G = map[x][y].G - img->map[x][y].G;
			result->map[x][y].B = map[x][y].B - img->map[x][y].B;
		}
	}
	return result;
}

void image::printImage() {
	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			printf("%d|%d|%d ", map[x][y].R, map[x][y].G, map[x][y].B);
		}
		printf("\n");
	}
}
