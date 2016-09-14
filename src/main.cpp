#include <netpbmManager.hpp>

int main () {
	imageManager *manager;

	// ...
	manager = new netpbmManager();
	// ...

	image *img = manager->load("pepe");
	manager->store(img);

	delete manager;
	delete img;

	return 0;
}