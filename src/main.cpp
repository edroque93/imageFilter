#include <netpbmManager.hpp>
#include <kernel.hpp>

int main () {
	struct kernel::kernelInfo info;
	info.type = kernel::GAUSSIAN;
	info.data.gaussian = {
		.sigma = 1.0,
		.radius = 2
	};
	kernel k(&info);
	//kernel k(
	//	5,5,
	//	1,4,7,4,1,
	//	4,16,26,16,4,
	//	7,26,41,26,7,
	//	4,16,26,16,4,
	//	1,4,7,4,1);
	//k.divisor = 273;
	imageManager *manager = new netpbmManager();
	image *original = manager->load("original.ppm");

	image *buffer = manager->load("original.ppm");;
	image *blur;
	for (int i = 0; i < 20; i++) {
		blur = buffer->applyKernel(&k);
		delete buffer;
		buffer = blur;
		image *sub = blur->substractImage(original);
		char buf[32];
		sprintf(buf, "edge_%d.ppm", i);
		manager->store(sub, buf);
		delete sub;
	}
	manager->store(blur, "blur.ppm");
	image *sub = blur->substractImage(original);
	manager->store(sub, "edge.ppm");

	return 0;
}
