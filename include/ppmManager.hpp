#ifndef PPM_MANAGER_HPP
#define PPM_MANAGER_HPP

#include <imageManager.hpp>
#include <image.hpp>

class ppmManager: public imageManager {
	public: 
		image load(char const* file);
		bool store(image img);
};

#endif