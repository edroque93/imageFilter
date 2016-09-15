#include <netpbmManager.hpp>


int main () {
	imageManager *manager;

	// ...
	manager = new netpbmManager();
	// ...

	image *img = manager->load("test.ppm");
	manager->store(img);

	delete manager;
	delete img;

	return 0;
}