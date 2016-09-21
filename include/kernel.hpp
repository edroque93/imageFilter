#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <macros.hpp>

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <cstdarg>

class kernel {
	public:
		enum kernelType {
			INDETITY, GAUSSIAN
		};

		union kernelData {
			struct {
				int32_t radius;
			} none;
			struct {
				double sigma;
				int32_t radius;
			} gaussian;
		};

		struct kernelInfo {
			enum kernelType type;
			union kernelData data;
		};

		int32_t **matrix;
		uint32_t width, height, divisor;

		kernel(struct kernelInfo *info);
		kernel(uint32_t width, uint32_t height, ...);
		kernel(uint32_t width, uint32_t height);
		~kernel();

	private:
		void allocMatrix();
		void initializeMatrix();
		void processGaussian(struct kernelInfo *info);
		double gauss2D(double x, double y, double sigma);
		double gauss2Dint(double x, double y, double sigma, double offset, double interval);
};

#endif
