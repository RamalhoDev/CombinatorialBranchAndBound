#include "../include/Subgradient.hpp"

double Subgradient::solve(Data *data) {
	double e = 1;
	int k = 0;
	double ub = INFINITE;
	double bestCost = INFINITE;
	vector<int> lambda = vector<int>(data->getDimension(), 0);
	vector<int> bestLambda;
	while (1) {
		auto kruskal = make_shared<Kruskal>(data->getMatrixCostPointer(), &lambda);
		auto solution = getOneTree(data, kruskal, &lambda);
		double cost = solution->getLowerBound();

		if (cost > bestCost) {
			bestCost = cost;
			bestSolution = solution;
			bestLambda = lambda;
			continue;
		}

		k = k + 1;
		if (k > kMax) {
			k = 0;
			e = e / 2;
		}
		double u = e * (ub - cost);


		if (e < 0.001) break;
	}

	return bestCost;
}
shared_ptr<vector<pair<int, int>>> Subgradient::getForbiddenArcs() { return this->bestSolution->getForbiddenArcs(); }

shared_ptr<SubgradientSolution> Subgradient::getOneTree(Data * data, shared_ptr<Kruskal> kruskal, vector<int> * lambda) {
	int dimension = data->getDimension();
	auto lb = kruskal->MST(dimension - 1);
	lb += data->getDistance(0, data->getFirstClosest()) + data->getDistance(0, data->getSecondClosest()) - lambda->at(data->getFirstClosest()) - lambda->at(data->getSecondClosest());
	for (size_t i = 1; i < lambda->size(); i++){
		lb += 2*lambda->at(i);
	}
	
	auto solutionEdges = kruskal->getEdges();
	solutionEdges.push_back(make_pair(0, data->getFirstClosest()));
	solutionEdges.push_back(make_pair(0, data->getSecondClosest()));

	return make_shared<SubgradientSolution>(lb, solutionEdges, dimension);
}