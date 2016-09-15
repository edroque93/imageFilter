#include <netpbmManager.hpp>

image *netpbmManager::load(char const *file) {
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
			processP3(handle, result);
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

void netpbmManager::processP3(FILE *handle, image *img) {
	ERROR("netpbmManager::processP3: TODO.");
}
