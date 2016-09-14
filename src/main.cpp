#include <netpbmManager.hpp>

typedef uint16_t colorSize;

int main () {
	imageManager<colorSize> *manager;

	// ...
	manager = new netpbmManager<colorSize>();
	// ...

	image<colorSize> *img = manager->load("test.ppm");
	manager->store(img);

	delete manager;
	delete img;

	return 0;
}