#include "../include/BranchAndBound.hpp"
#include "../include/Data.h"
#include "../include/Node.hpp"

int main(int argn, char** argv) {
	Data* data = new Data(argn, argv[1]);
	data->read();

	BranchAndBound bb = BranchAndBound(data);
	auto solution = bb.solve(false);
	double cost = 0;
	cout << solution[0] << " ";
	for (size_t i = 1; i < solution.size(); i++) {
		cout << solution[i] << " ";
		cost += data->getDistance(solution[i - 1], solution[i]);
	}
	cout << "\nCost: " << cost << "\n";

	return 0;
}