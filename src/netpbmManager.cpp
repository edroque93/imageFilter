#include <netpbmManager.hpp>

template <typename T>
image<T> *netpbmManager<T>::load(char const *file) {
	image<T> *result = NULL;

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

template <typename T>
bool netpbmManager<T>::store(image<T> *img) {
	return true;
}

template <typename T>
void netpbmManager<T>::processP3(FILE *handle, image<T> *img) {
	ERROR("netpbmManager::processP3: TODO.");
}

template class netpbmManager<uint16_t>;