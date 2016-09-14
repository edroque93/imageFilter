#include <ppmManager.hpp>

int main () {
	int a = 34;
	int b = 23;

	imageManager *manager;

	*manager = ppmManager();

	image img = manager->load("paco");

	return 0;
}