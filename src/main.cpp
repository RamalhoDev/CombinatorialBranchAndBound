#include "../include/BranchAndBound.hpp"
#include "../include/CombinatorialRelaxation.hpp"
#include "../include/Data.h"
#include "../include/Node.hpp"
#include "../include/Subgradient.hpp";
int main(int argn, char** argv) {
	Data* data = new Data(argn, argv[1]);
	data->read();
	// auto solver = make_shared<CombinatorialRelaxation>();
	auto solver = make_shared<Subgradient>(10);
	solver->solve(data);
	// BranchAndBound bb = BranchAndBound(data, solver);
	// auto solution = bb.solve();
	// double cost = 0;
	// cout << solution->at(0) << " ";
	// for (size_t i = 1; i < solution->size(); i++) {
	// 	cout << solution->at(i) << " ";
	// 	cost += data->getDistance(solution->at(i - 1), solution->at(i));
	// }
	// cout << "\nCost: " << cost << "\n";

	return 0;
}