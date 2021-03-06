#ifndef IMAGE_MANAGER_HPP
#define IMAGE_MANAGER_HPP

#include <image.hpp>

class imageManager {
	public: 
		virtual image *load(const char *file) = 0;
		virtual bool store(image *img, const char *name) = 0;
};

#endif