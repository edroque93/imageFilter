#ifndef IMAGE_MANAGER_HPP
#define IMAGE_MANAGER_HPP

#include <image.hpp>

template <typename T>
class imageManager {
	public: 
		virtual image<T> *load(char const *file) = 0;
		virtual bool store(image<T> *img) = 0;
};

#endif