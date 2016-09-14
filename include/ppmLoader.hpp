#ifndef PPM_LOADER_HPP
#define PPM_LOADER_HPP

#include <imageLoader.hpp>
#include <image.hpp>

class ppmLoader: public imageLoader {
	public: 
		image load(char const* file);
};

#endif