#include <kernel.hpp>

kernel::kernel(struct kernelInfo *info) {
	switch (info->type) {
		case INDETITY:
			break;
		case GAUSSIAN:
			processGaussian(info);
	}
}

kernel::kernel(uint32_t width, uint32_t height, ...) {
	this->width = width;
	this->height = height;
	this->divisor = 1;
	allocMatrix();
	va_list arguments;
	va_start(arguments, height);
	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			matrix[x][y] = va_arg(arguments, int32_t);
		}
	}
	va_end(arguments);
}

kernel::kernel(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	this->divisor = 1;
	allocMatrix();
	initializeMatrix();
}

kernel::~kernel() {
	for (uint32_t i = 0; i < width; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void kernel::allocMatrix() {
	matrix = (int32_t **) malloc(width * sizeof(int32_t *));
	for (uint32_t i = 0; i < width; i++) {
		matrix[i] = (int32_t *) malloc(height * sizeof(int32_t));
	}
}

void kernel::initializeMatrix() {
	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			matrix[x][y] = 0;
		}
	}
}

void kernel::processGaussian(struct kernelInfo *info) {
	auto gauss = info->data.gaussian;
	this->width = 1 + gauss.radius * 2;
	this->height = this->width;
	allocMatrix();
	const double sigmas = 2.6;
	double sqrtCell = 2*sigmas*gauss.sigma/this->width;
	double integral[this->width][this->height];
	for (int32_t y = 0; y < this->height; y++) {
		for (int32_t x = 0; x < this->width; x++) {
			double sum = 0.;
			int divisions = 0;
			for (double j = -sigmas*gauss.sigma+y*sqrtCell; j < -sigmas*gauss.sigma+y*sqrtCell+sqrtCell; j+=0.001) {
				for (double i = -sigmas*gauss.sigma+x*sqrtCell; i < -sigmas*gauss.sigma+x*sqrtCell+sqrtCell; i+=0.001) {
					sum += 
						(1 / (2 * M_PI * gauss.sigma * gauss.sigma)) *
						pow(M_E, -((i * i + j * j) / (2 * gauss.sigma * gauss.sigma)));
					divisions++;
				}
			}
			integral[x][y] = sum / divisions;
		}
	}
	this->divisor = round(1./integral[0][0]);
	for (int32_t y = 0; y < this->height; y++) {
		for (int32_t x = 0; x < this->width; x++) {
			matrix[x][y] = this->divisor * integral[x][y];
		}
	}
}

