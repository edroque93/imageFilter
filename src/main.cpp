#include <netpbmManager.hpp>


int main () {
	imageManager *manager;
	// ...
	manager = new netpbmManager();


	//image *img = manager->load("test.ppm");
	image *img = manager->load("original.ppm");
	image *sub = manager->load("test.ppm");

	int32_t **matrix = (int32_t **) malloc(5 * sizeof(int32_t *));
	for (size_t i = 0; i < 5; i++) {
		matrix[i] = (int32_t *) malloc(5 * sizeof(int32_t));
	}

	matrix[0][0] = 1;
	matrix[1][0] = 4;
	matrix[2][0] = 7;
	matrix[3][0] = 4;
	matrix[4][0] = 1;

	matrix[0][1] = 4;
	matrix[1][1] = 16;
	matrix[2][1] = 26;
	matrix[3][1] = 16;
	matrix[4][1] = 4;

	matrix[0][2] = 7;
	matrix[1][2] = 26;
	matrix[2][2] = 41;
	matrix[3][2] = 26;
	matrix[4][2] = 7;

	matrix[0][3] = 4;
	matrix[1][3] = 16;
	matrix[2][3] = 26;
	matrix[3][3] = 16;
	matrix[4][3] = 4;

	matrix[0][4] = 1;
	matrix[1][4] = 4;
	matrix[2][4] = 7;
	matrix[3][4] = 4;
	matrix[4][4] = 1;

/* SHARPEN
	matrix[0][0] = 0;
	matrix[1][0] = -1;
	matrix[2][0] = 0;

	matrix[0][1] = -1;
	matrix[1][1] = 5;
	matrix[2][1] = -1;

	matrix[0][2] = 0;
	matrix[1][2] = -1;
	matrix[2][2] = 0;
*/

/* BLUR
	matrix[0][0] = 1;
	matrix[1][0] = 1;
	matrix[2][0] = 1;
	matrix[0][1] = 1;
	matrix[1][1] = 1;
	matrix[2][1] = 1;
	matrix[0][2] = 1;
	matrix[1][2] = 1;
	matrix[2][2] = 1;
*/
/*
	matrix[0][0] = 1;
	matrix[1][0] = 2;
	matrix[2][0] = 1;
	matrix[0][1] = 2;
	matrix[1][1] = 4;
	matrix[2][1] = 2;
	matrix[0][2] = 1;
	matrix[1][2] = 2;
	matrix[2][2] = 1;
*/
	//image *ker = img->applyKernel(matrix, 5, 5);
	//manager->store(ker, "result.ppm");

	image *result = sub->substractImage(img);
	manager->store(result, "result.ppm");

	delete manager;
	delete img;

	return 0;
}