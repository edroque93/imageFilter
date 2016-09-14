#include <image.hpp>

image::image(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	map = (image::pixel **) malloc(width * sizeof(image::pixel *));
	for (uint32_t i = 0; i < width; i++) {
		map[i] = (image::pixel *) malloc(height * sizeof (image::pixel));
	}
}

image::~image() {

}

void image::initializeMap() {
	
}