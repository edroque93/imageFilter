#include <ppmLoader.hpp>

int main () {
	int a = 34;
	int b = 23;

	imageLoader *loader;

	*loader = ppmLoader();

	loader->load("paco");
	
	return 0;
}