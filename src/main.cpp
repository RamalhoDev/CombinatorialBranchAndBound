#include <stdlib.h>

#include "../include/BranchAndBound.hpp"
#include "../include/CombinatorialRelaxation.hpp"
#include "../include/Data.h"
#include "../include/Node.hpp"
#include "../include/Subgradient.hpp";
int main(int argn, char** argv) {
	Data* data = new Data(argn, argv[1]);
	data->read();
	double ub = atof(argv[2]);

	// data = new Data();
	// data->updateClosest();
	// auto solver = make_shared<CombinatorialRelaxation>();
	auto subgradientSolver = make_shared<Subgradient>(30, ub);
	// auto lambda = make_shared<vector<double>>(5, 0);
	// subgradientSolver->solve(data, lambda);
	BranchAndBound bb = BranchAndBound(data, subgradientSolver);
	auto solution = bb.solve();
	double cost = 0;
	vector<vector<int>> newSolution = vector<vector<int>>(data->getDimension(), vector<int>());

	for (size_t i = 0; i < solution->size(); i++) {
		cost += data->getDistance(solution->at(i).first, solution->at(i).second);
		cout << solution->at(i).first << " " << solution->at(i).second << endl;
	}

	cout << "\nCost: " << cost << "\n";

	return 0;
}