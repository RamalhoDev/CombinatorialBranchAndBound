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
	auto solver = make_shared<CombinatorialRelaxation>();
	auto subgradientSolver = make_shared<Subgradient>(30, ub);
	BranchAndBound bb = BranchAndBound(data, subgradientSolver);
	auto solution = bb.solve();
	double cost = 0;
	vector<vector<int>> newSolution = vector<vector<int>>(data->getDimension(), vector<int>());
	for (size_t i = 0; i < solution->size(); i++) {
		newSolution[solution->at(i).first].push_back(solution->at(i).second);
	}

	cout << 0 << " ";
	int start = 0;
	for (size_t i = 1; i < newSolution.size(); i++) {
		cout << newSolution[start][0] << " ";
		cost += data->getDistance(start, newSolution[start][0]);
		start = newSolution[start][0];
	}
	cout << "\nCost: " << cost << "\n";

	return 0;
}