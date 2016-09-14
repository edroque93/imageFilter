#ifndef NETPBM_MANAGER_HPP
#define NETPBM_MANAGER_HPP

#include <imageManager.hpp>
#include <image.hpp>
#include <macros.hpp>
#include <stdio.h>

class netpbmManager: public imageManager {
	public:
		char type[2];
		
		image *load(char const *file);
		bool store(image *img);
};

#endif