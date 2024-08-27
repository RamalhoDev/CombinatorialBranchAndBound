#include "../include/BranchAndBound.hpp"
#include "../include/Data.h"

int main(int argn, char** argv) {
	Data* data = new Data(argn, argv[1]);
	data->read();
	data->printMatrixDist();
	return 0;
}