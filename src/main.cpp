#include <netpbmManager.hpp>


int main () {
	imageManager *manager;

	// ...
	manager = new netpbmManager();
	// ...

	image *img = manager->load("tux.ppm");
	//img->printImage();
	manager->store(img, "paco.ppm");

	delete manager;
	delete img;

	return 0;
}