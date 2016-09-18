#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <macros.hpp>
#include <stdint.h>
#include <stdlib.h>

class kernel {
	public:
		int32_t **matrix;
		uint32_t width, height;

		kernel(uint32_t width, uint32_t height);
		~kernel();

	private:
		void initializeMatrix();
};

#endif