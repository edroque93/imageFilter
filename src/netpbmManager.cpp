#include <netpbmManager.hpp>

image *netpbmManager::load(const char *file) {
	image *result = NULL;

	FILE *handle = fopen(file, "rb");
	if (handle == NULL) {
		ERROR("netpbmManager::load: cannot open file.");
	}

	fread(&type, sizeof(char), 2, handle);

	if (type[0] != 'P') {
		ERROR("netpbmManager::load: file is not Netpbm compliant.");
	}

	switch (type[1]) {
		case '3': {
			result = processP3(handle);
			break;
		}
		default: {
			ERROR("netpbmManager::load: file is not (yet) supported.");
		}
	}

	fclose(handle);

	return result;
}

bool netpbmManager::store(image *img) {
	return true;
}

image *netpbmManager::processP3(FILE *handle) {
	image *img = NULL;
	uint32_t width = 0, height = 0, maxValue = 0;
	uint8_t rgb = 0;
	uint8_t pWidth = 0, pHeight = 0;
	size_t read;
	char buffer[scoop];
	do {
		read = fread(&buffer, sizeof(char), scoop, handle);
		size_t pointer = 0;
		while (pointer < read) {
			if (strchr(whitespace, buffer[pointer]) != NULL) {
				pointer++;
			} else {
				while (buffer[pointer] == comment) {
					while (buffer[++pointer] != newline);
					pointer++;
				}
				if (!width) {
					width = getUint32(buffer, read, &pointer);
				}
				if (!height) {
					height = getUint32(buffer, read, &pointer);
				}
				if (!maxValue) {
					maxValue = getUint32(buffer, read, &pointer);
					img = new image(width, height);
				}
				if (width && height && maxValue) {
					switch (rgb) {
						case 0: 
							img->map[pWidth][pHeight].R = getUint32(buffer, read, &pointer);
							break;
						case 1: 
							img->map[pWidth][pHeight].G = getUint32(buffer, read, &pointer);
							break;
						case 2: 
							img->map[pWidth][pHeight].B = getUint32(buffer, read, &pointer);
							break;
						default:
							break;
					}
					rgb = (rgb + 1) % 3;
					if (rgb == 0) {
						if ((pWidth + 1) == width) {
							pHeight++;
							pWidth = 0;
						} else {
							pWidth++;
						}
					}
				}
			}
		}
	} while (read == scoop);

	return img;
}

uint32_t netpbmManager::getUint32(char *buffer, size_t size, size_t *pointer) {
	size_t start = *pointer;
	while ((*pointer < size) && (strchr(whitespace, buffer[++(*pointer)]) == NULL));
	size_t valueSize = *pointer - start;
	char value[valueSize + 1];
	memcpy(value, &buffer[start], valueSize);
	value[valueSize] = '\0';
	return (uint32_t) atoll(value);
}