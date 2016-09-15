#ifndef NETPBM_MANAGER_HPP
#define NETPBM_MANAGER_HPP

#include <imageManager.hpp>
#include <image.hpp>
#include <macros.hpp>

#include <stdio.h>
#include <string.h>

class netpbmManager: public imageManager {
	public:
		image *load(const char *file);
		bool store(image *img, const char *name);

	private:
		const char *whitespace = "\n\r\t ";
		char comment = '#';
		char newline = '\n';
		size_t scoop = 4096;
		size_t scoopPad = 64;
		char type[2];

		image *processP3(FILE *handle);
		uint32_t getUint32(char *buffer, size_t size, size_t *pointer); 
};

#endif