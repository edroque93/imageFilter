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

bool netpbmManager::store(image *img, const char *name) {
	FILE *handle = fopen(name, "wb");
	if (handle == NULL) {
		ERROR("netpbmManager::store: cannot open file.");
	}
	fprintf(handle, "P3\n"); // TODO preserve last used format if not specified?
	fprintf(handle, "# Image generated by netpbmManager\n");
	fprintf(handle, "%d %d\n%d\n", img->width, img->height, img->depth);
	for (size_t y = 0; y < img->height; y++) {
		int count = 0;
		for (size_t x = 0; x < img->width; x++) {
			// TODO normalize colors to maxvalue
			fprintf(handle, "%d %d %d ", img->map[x][y].R, img->map[x][y].G, img->map[x][y].B);
			count++;
			if (count == 6) {
				fprintf(handle, "\n");
				count = 0;
			} // TODO prettify this so each line contains +- 70 characters
		}
	}

	fclose(handle);

	return true;
}

image *netpbmManager::processP3(FILE *handle) {
	image *img = NULL;
	uint32_t width = 0, height = 0, maxValue = 0;
	uint32_t pWidth = 0, pHeight = 0;
	uint8_t rgb = 0;
	size_t read;
	char buffer[scoop];
	size_t realPad = 0;
	bool usingAux = false;

	do {
		if (usingAux) {
			memcpy(buffer, &buffer[scoop-realPad], realPad);
			read = fread(&buffer[realPad], sizeof(char), scoop-realPad, handle) + realPad;
			usingAux = false;
		} else {
			read = fread(&buffer, sizeof(char), scoop, handle);
			realPad = 0;
		}
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
					img = new image(width, height, maxValue);
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
						if (read == scoop) {
							if ((pointer + scoopPad) >= scoop) {
								realPad = scoop - pointer;
								usingAux = true;
								break;
							}
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