#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include <image.hpp>

class image_loader {
	public: 
		virtual image load(char* file) = 0;
};

#endif