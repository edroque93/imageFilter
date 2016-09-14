#include <netpbmManager.hpp>

image *netpbmManager::load(char const *file) {
	image *result = NULL;

	FILE *handle = fopen(file, "rb");
	if (handle != NULL) {
		fread(&type, sizeof(char), 2, handle);
		if (type[0] != 'P') {
			ERROR("netpbmManager::load: file provided is not a Netpbm compliant file.");
		}

		fclose(handle);
	}
	
	return result;
}

bool netpbmManager::store(image *img) {
	return true;
}