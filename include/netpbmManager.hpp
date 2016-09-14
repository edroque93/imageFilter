#ifndef NETPBM_MANAGER_HPP
#define NETPBM_MANAGER_HPP

#include <imageManager.hpp>
#include <image.hpp>
#include <macros.hpp>
#include <stdio.h>

template <typename T>
class netpbmManager: public imageManager<T> {
	public:
		char type[2];
		
		image<T> *load(char const *file);
		bool store(image<T> *img);
	private:
		void processP3(FILE *handle, image<T> *img);
};

#endif