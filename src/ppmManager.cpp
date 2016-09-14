#include <ppmManager.hpp>

//
#include <stdio.h>
//

image ppmManager::load(char const *file) {
	printf("%s", file);
	return image(1,1);
}

bool ppmManager::store(image img) {
	return true;
}