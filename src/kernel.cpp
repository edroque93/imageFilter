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
	const double radius = 2.39;
	double division = (2*radius*gauss.sigma)/(this->width);
	double integral[this->width][this->height];
	for (int32_t y = 0; y < this->height; y++) {
		for (int32_t x = 0; x < this->width; x++) {
			double p_x = -radius * gauss.sigma + x * division;
			double p_y = -radius * gauss.sigma + y * division;
			integral[x][y] = gauss2Dint(p_x, p_y, gauss.sigma, division, 0.001);
		}
	}
	this->divisor = ceil(1./integral[0][0]);
	for (int32_t y = 0; y < this->height; y++) {
		for (int32_t x = 0; x < this->width; x++) {
			matrix[x][y] = this->divisor * integral[x][y];
			printf("%d ", matrix[x][y]);
		}
		printf("\n");
	}
}

double kernel::gauss2D(double x, double y, double sigma) {
	return 
		(1 / (2 * M_PI * sigma * sigma)) * 
		pow(M_E, -((x * x + y * y) / (2 * sigma * sigma)));
}

double kernel::gauss2Dint(double x, double y, double sigma, double offset, double interval) {
	double integral = 0.;
	int it = 0;
	for (double i = x; i < x+offset; i += interval) {
		for (double j = y; j < y+offset; j += interval) {
			integral += gauss2D(i, j, sigma);
			it++;
		}
	}
	return integral/it;
}

