#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include <image.hpp>

class imageLoader {
	public: 
		virtual image load(char const* file) = 0;
};

#endif