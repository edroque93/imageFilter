#include <image.hpp>

template <typename T>
image<T>::image(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	map = (image::pixel **) malloc(width * sizeof(image::pixel *));
	for (uint32_t i = 0; i < width; i++) {
		map[i] = (image::pixel *) malloc(height * sizeof(image::pixel));
	}
	initializeMap();
}

template <typename T>
image<T>::~image() {
	for (uint32_t i = 0; i < width; i++) {
		free(map[i]);
	}
	free(map);
}

template <typename T>
void image<T>::initializeMap() {
	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			map[x][y].R = map[x][y].G = map[x][y].B = 0;
		}
	}
}

template <typename T>
void image<T>::applyKernel(int32_t **matrix, int32_t rows, int32_t columns) {
	return;
}

template class image<uint16_t>;
template class image<uint32_t>;