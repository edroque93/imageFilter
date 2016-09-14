#include <netpbmManager.hpp>

int main () {
	imageManager<uint16_t> *manager;

	// ...
	manager = new netpbmManager<uint16_t>();
	// ...

	image<uint16_t> *img = manager->load("test.ppm");
	manager->store(img);

	delete manager;
	delete img;

	return 0;
}