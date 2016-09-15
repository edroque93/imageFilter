#ifndef IMAGE_MANAGER_HPP
#define IMAGE_MANAGER_HPP

#include <image.hpp>

class imageManager {
	public: 
		virtual image *load(char const *file) = 0;
		virtual bool store(image *img) = 0;
};

#endif