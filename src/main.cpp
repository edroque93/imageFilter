#include <netpbmManager.hpp>
#include <kernel.hpp>

int main () {
	struct kernel::kernelInfo info;
	info.type = kernel::GAUSSIAN;
	info.data.gaussian = {
		.sigma = 1.0,
		.radius = 2
	};
	//kernel k(&info); // integral is failing
	kernel k(
		5,5,
		1,4,7,4,1,
		4,16,26,16,4,
		7,26,41,26,7,
		4,16,26,16,4,
		1,4,7,4,1);
	k.divisor = 273;
	imageManager *manager = new netpbmManager();
	image *original = manager->load("test.ppm");

	image *buffer = manager->load("test.ppm");;
	image *blur;
	for (size_t i = 0; i < 40; i++) {
		blur = buffer->applyKernel(&k);
		delete buffer;
		buffer = blur;
	}
	manager->store(blur, "blur.ppm");
	image *sub = blur->substractImage(original);
	manager->store(sub, "edge.ppm");

	return 0;
}